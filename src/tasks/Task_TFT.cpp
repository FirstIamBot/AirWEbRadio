/*
 *Using LVGL with Arduino requires some extra steps:
 *Be sure to read the docs here: https://docs.lvgl.io/master/get-started/platforms/arduino.html  
 */
#include "Task_TFT.h"

#include <SPI.h>
#include <FS.h>
#include "SPIFFS.h" // ESP32 only
#include <LittleFS.h>
#include <WiFi.h>
#include <Wire.h>

#include <lvgl.h>
#include <TFT_eSPI.h>
#include "gui/gui.h"

#include "lvgl_touch_calibration/lv_tc.h"
#include "lvgl_touch_calibration/lv_tc_screen.h"
#include "lvgl_touch_calibration/esp_nvs_tc.h"

#include <AiEsp32RotaryEncoder.h>
/**********************
 *   DEFINES
 **********************/
#define LV_TICK_PERIOD_MS 30
//********************************     Rotary Encoder    ******************************
#define ROTARY_ENCODER_A_PIN      3  // CLK(А)     синий   25 
#define ROTARY_ENCODER_B_PIN      1  // DT(В)      зелёный 26
#define ROTARY_ENCODER_BUTTON_PIN 13  // SW(Button) фиолетовый
#define ROTARY_ENCODER_VCC_PIN   -1   //
//depending on your encoder - try 1,2 or 4 to get expected behaviour
//#define ROTARY_ENCODER_STEPS 1
//#define ROTARY_ENCODER_STEPS 2
#define ROTARY_ENCODER_STEPS 4
/**********************
 *  STATIC PROTOTYPES
 **********************/
static void encoder_init(void);
static void encoder_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static void encoder_handler(void);
void tc_finish_cb(lv_event_t *event) ;
void disp_flush( lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p );
void touchpad_read( lv_indev_drv_t * indev_drv, lv_indev_data_t * data );
void initTFT();
void initCalTFT(void);

AiEsp32RotaryEncoder Encoder = AiEsp32RotaryEncoder(
                    ROTARY_ENCODER_A_PIN, \
                    ROTARY_ENCODER_B_PIN, \
                    ROTARY_ENCODER_BUTTON_PIN, \
                    ROTARY_ENCODER_VCC_PIN, \
                    ROTARY_ENCODER_STEPS);


void IRAM_ATTR EncoderISR()
{
  Encoder.readEncoder_ISR();
}
//######################################################################################
lv_indev_t * indev_touchpad;
lv_indev_t * indev_encoder;
static lv_indev_t * indev_button;

static lv_indev_drv_t touch_indev_drv;
static lv_indev_drv_t encoder_indev_drv;

int32_t encoder_diff;
static lv_indev_state_t encoder_state;

//######################## Extern variable from GUI  ###################################

//######################################################################################
static const uint16_t screenWidth  = 320;
static const uint16_t screenHeight = 240;
TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * screenHeight / 10 ];

extern Data_GUI_Air xTransmitGUItoSI4735;
Data_Air_GUI xResivedSI4735fromdGUI;  
//######################################################################################
extern SemaphoreHandle_t xSemaphoreSPI;

extern QueueHandle_t xQueueGUItoSI4735; // Очередь для передачи с GUI на Si4735
extern QueueHandle_t xQueueSI4735toGUI; // Очередь для передачи с Si4735 на GUI
char valFreq[15];
//######################################################################################
#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char * buf)
{
    Serial.printf(buf);
    Serial.flush();
}
#endif



void Task_TFT(void *pvParameters) 
{
    (void)pvParameters;

    Serial.begin( 115200 ); /* prepare for possible serial debug */

    String LVGL_Arduino = "Hello Arduino! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

    Serial.println( LVGL_Arduino );
    Serial.println( "I am LVGL_Arduino" );
    /*  
    initTFT();
    gui_meter();
    lv_test();
    gui_meter();
    gui_bar();
    lv_widgets(); 
    */
    initCalTFT();
    Serial.println( "Hello LVGL" );
    
    while (1) // A Task shall never return or exit.
    {
        /* Delay 1 tick (assumes FreeRTOS tick is 10ms */
        //vTaskDelay(pdMS_TO_TICKS(10));
        /* Try to take the semaphore, call lvgl related function on success  */

        if (pdTRUE == xSemaphoreTake(xSemaphoreSPI, portMAX_DELAY)) {
            lv_task_handler();
            lv_tick_inc(LV_TICK_PERIOD_MS);
            xSemaphoreGive(xSemaphoreSPI);
        }
        else{
            Serial.println("Semaphore dont Take ");
        }
        /*
            Передаём данные из xTransmitGUItoSI4735 в очередь xQueueGUItoSI4735
            для управления Si4735
        */
        if(xTransmitGUItoSI4735.State == true)
        {
		    if( xQueueSend( xQueueGUItoSI4735, &xTransmitGUItoSI4735, portMAX_DELAY ) != pdPASS )
            // if( xQueueSend( xQueueGUItoSI4735, &xReceivedGUItoSI4735, 500 ) != pdPASS ) 
		    {
                Serial.println("We could not write to the queue because it was full  this must\
                                be an error as the queue should never contain more than one item!");
		    }
            xTransmitGUItoSI4735.State = false;
        }
        /*
            Передаём данные через xResivedSI4735fromdGUI(Si4735) для отображения в GUI
        */
        if (pdTRUE == xQueueReceive( xQueueSI4735toGUI, &xResivedSI4735fromdGUI, pdPASS))
        {
            awgui_reload(xResivedSI4735fromdGUI);
        }

/*
        xSemaphoreTake(xSemaphoreSPI, portMAX_DELAY);
        lv_task_handler();
        lv_tick_inc(LV_TICK_PERIOD_MS);
        xSemaphoreGive(xSemaphoreSPI);
*/
    }
}
//######################################################################################
/*Initialize your encoder*/
static void encoder_init(void)
{
    Encoder.begin();
    Encoder.setup(EncoderISR);
    //Encoder.setup([]{Encoder.readEncoder_ISR();}); // установка прерываний для Энкодера
    //optionally we can set boundaries and if values should cycle or not
    bool circleValues = false;
    Encoder.setBoundaries(0, 100, circleValues);// Установка границы от текущей темрературы до максимальной
    Encoder.setAcceleration(50); //or set the value - larger number = more accelearation; 0 or 1 means disabled acceleration
    //Encoder.disableAcceleration(); //acceleration is now enabled by default - disable if you dont need it
    Encoder.setEncoderValue(50); // init start value rotary encoder
    Serial.println("Encoder init");

}
/*Will be called by the library to read the encoder*/
static void encoder_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    if(Encoder.encoderChanged())
	{
        data->enc_diff = Encoder.readEncoder();
        Serial.print("encoder_diff = ");Serial.println(data->enc_diff);
        /*
        if (data->enc_diff != 0) {
	    data->key = data->enc_diff < 0 ? LV_KEY_LEFT : LV_KEY_RIGHT;
	    }
        */
        if ((encoder_diff - data->enc_diff) > 0) {
	        data->key = LV_KEY_UP;
            encoder_diff = data->enc_diff;
	    }
        else{
            data->key = LV_KEY_DOWN;
            encoder_diff = data->enc_diff;
        }
	}
    if(Encoder.isEncoderButtonDown()) data->state = LV_INDEV_STATE_PRESSED;
    else data->state = LV_INDEV_STATE_RELEASED;
}
/*Call this function in an interrupt to process encoder events (turn, press)*/
static void encoder_handler(void)
{
    /*Your code comes here*/
    encoder_diff += 0;
    encoder_state = LV_INDEV_STATE_REL;
    Serial.print("encoder_state = ");Serial.println(LV_INDEV_STATE_REL);
}
/* Your callback for when the calibration finishes */
void tc_finish_cb(lv_event_t *event) {
    /* Load the application */
    awgui(); /* Implement this */
};
/* Display flushing */
void disp_flush( lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = ( area->x2 - area->x1 + 1 );
    uint32_t h = ( area->y2 - area->y1 + 1 );

    tft.startWrite();
    tft.setAddrWindow( area->x1, area->y1, w, h );
    tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
    tft.endWrite();

    lv_disp_flush_ready( disp_drv );
}
/*Read the touchpad*/
void touchpad_read( lv_indev_drv_t * indev_drv, lv_indev_data_t * data )
{
    uint16_t touchX, touchY;

    bool touched = tft.getTouch( &touchX, &touchY, 600 );

    if( !touched )
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        data->state = LV_INDEV_STATE_PR;

        /*Set the coordinates*/
        data->point.x = touchX;
        data->point.y = touchY;

        //Serial.print( "Data x = " ); Serial.println( touchX );
        //Serial.print( "Data y = " ); Serial.println( touchY );
    }
}
/* Init TFT without calibrate */
void initTFT() 
{
    lv_init();

#if LV_USE_LOG != 0
    lv_log_register_print_cb( my_print ); /* register print function for debugging */
#endif

    tft.begin();          /* TFT init */
    tft.initDMA();
    tft.setRotation( 3 ); /* Landscape orientation, flipped */
    uint16_t calData[5] = {174, 2543, 208, 4574, 1};
    tft.setTouch( calData );

    lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * screenHeight / 10 );

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );

    /*Initialize the (dummy) input device driver*/
    /*------------------
     * Encoder
     * -----------------*/
    /*Initialize your encoder if you have*/
    encoder_init();
    /*Register a encoder input device*/
    lv_indev_drv_init(&encoder_indev_drv);
    encoder_indev_drv.type = LV_INDEV_TYPE_ENCODER;
    encoder_indev_drv.read_cb = encoder_read;
    indev_encoder = lv_indev_drv_register(&encoder_indev_drv);
    /*------------------
     * TouchPad
     * -----------------*/
    lv_indev_drv_init( &touch_indev_drv );
    touch_indev_drv.type = LV_INDEV_TYPE_POINTER;
    touch_indev_drv.read_cb = touchpad_read;
    indev_touchpad = lv_indev_drv_register(&touch_indev_drv);
}
/* Init TFT without calibrate */
void initCalTFT(void)
{
    lv_init();

#if LV_USE_LOG != 0
    lv_log_register_print_cb( my_print ); /* register print function for debugging */
#endif

    tft.begin();          /* TFT init */
    tft.setRotation( 3 ); /* Landscape orientation, flipped */
    
    tft.initDMA();

    lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * screenHeight / 10 );

    /*Initialize the display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init( &disp_drv );
    /*Change the following line to your display resolution*/
    disp_drv.hor_res = screenWidth;
    disp_drv.ver_res = screenHeight;
    disp_drv.flush_cb = disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );
   /*------------------
     * Encoder
     * -----------------*/
    /*Initialize your encoder if you have*/
    encoder_init();
    /*Register a encoder input device*/
    lv_indev_drv_init(&encoder_indev_drv);
    encoder_indev_drv.type = LV_INDEV_TYPE_ENCODER;
    encoder_indev_drv.read_cb = encoder_read;

    indev_encoder = lv_indev_drv_register(&encoder_indev_drv);

    //lv_indev_drv_t indevDrv;

    lv_tc_indev_drv_init(&touch_indev_drv, touchpad_read);
    /* Register the driver. */
    lv_indev_drv_register(&touch_indev_drv);

    indev_touchpad = lv_indev_drv_register(&touch_indev_drv);

    /* If using NVS: Register a calibration coefficients save callback. */
    lv_tc_register_coeff_save_cb(esp_nvs_tc_coeff_save_cb);
    /* Create the calibration screen. */
    lv_obj_t *tCScreen = lv_tc_screen_create();
    /* Register a callback for when the calibration finishes. An LV_EVENT_READY event is triggered. */
    lv_obj_add_event_cb(tCScreen, tc_finish_cb, LV_EVENT_READY, NULL);
    /* If using NVS: Init NVS and check for existing calibration data. */
    if(esp_nvs_tc_coeff_init()) {
        lv_obj_clean(lv_scr_act()); // Очистка экрана
        awgui(); /* Implement this */
    } else {
        /* There is no data: load the calibration screen, perform the calibration */
        lv_disp_load_scr(tCScreen);
        lv_tc_screen_start(tCScreen);
    }

}
