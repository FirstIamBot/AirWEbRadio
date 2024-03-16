/*
 *Using LVGL with Arduino requires some extra steps:
 *Be sure to read the docs here: https://docs.lvgl.io/master/get-started/platforms/arduino.html  
 */
#include <Arduino.h>
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

/**********************
 *   DEFINES
 **********************/
#define LV_TICK_PERIOD_MS 10
/**********************
 *  STATIC PROTOTYPES
 **********************/

static const uint16_t screenWidth  = 320;
static const uint16_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * screenHeight / 10 ];

TFT_eSPI tft = TFT_eSPI(screenWidth, screenHeight); /* TFT instance */

/* Your callback for when the calibration finishes */
void tc_finish_cb(lv_event_t *event) {
    /* Load the application */
    lv_test(); /* Implement this */
};

extern SemaphoreHandle_t xSemaphoreSPI;
//###################################################

//###################################################
#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char * buf)
{
    Serial.printf(buf);
    Serial.flush();
}
#endif
/* Display flushing */
void my_disp_flush( lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p )
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
void my_touchpad_read( lv_indev_drv_t * indev_drv, lv_indev_data_t * data )
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

        Serial.print( "Data x = " );
        Serial.println( touchX );

        Serial.print( "Data y = " );
        Serial.println( touchY );
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
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );

    /*Initialize the (dummy) input device driver*/
    /*------------------
     * TouchPad
     * -----------------*/
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init( &indev_drv );
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register( &indev_drv );

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
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register( &disp_drv );

    static lv_indev_drv_t indevDrv;
    lv_tc_indev_drv_init(&indevDrv, my_touchpad_read);
    /* Register the driver. */
    lv_indev_drv_register(&indevDrv);
    /* If using NVS: Register a calibration coefficients save callback. */
    lv_tc_register_coeff_save_cb(esp_nvs_tc_coeff_save_cb);
    /* Create the calibration screen. */
    lv_obj_t *tCScreen = lv_tc_screen_create();
    /* Register a callback for when the calibration finishes. An LV_EVENT_READY event is triggered. */
    lv_obj_add_event_cb(tCScreen, tc_finish_cb, LV_EVENT_READY, NULL);
    /* If using NVS: Init NVS and check for existing calibration data. */
    if(esp_nvs_tc_coeff_init()) {
        lv_obj_clean(lv_scr_act()); // Очистка экрана
        lv_test(); /* Implement this */
    } else {
        /* There is no data: load the calibration screen, perform the calibration */
        lv_disp_load_scr(tCScreen);
        lv_tc_screen_start(tCScreen);
    }

}

void Task_TFT(void *pvParameters) 
{
    (void)pvParameters;

    Serial.begin( 115200 ); /* prepare for possible serial debug */

    String LVGL_Arduino = "Hello Arduino! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();

    Serial.println( LVGL_Arduino );
    Serial.println( "I am LVGL_Arduino" );

   /*initTFT();
    lv_test();
    gui_meter();
    gui_bar();
    lv_widgets(); */
    initCalTFT();
    
    Serial.println( "Hello LVGL" );

    while (1) // A Task shall never return or exit.
    {
        /* Delay 1 tick (assumes FreeRTOS tick is 10ms */
        vTaskDelay(pdMS_TO_TICKS(10));

        /* Try to take the semaphore, call lvgl related function on success 
       if (pdTRUE == xSemaphoreTake(xSemaphoreSPI, portMAX_DELAY)) {
            lv_task_handler();
            lv_tick_inc(LV_TICK_PERIOD_MS);
            xSemaphoreGive(xSemaphoreSPI);
       }*/
       xSemaphoreTake(xSemaphoreSPI, portMAX_DELAY);
       lv_task_handler();
       lv_tick_inc(LV_TICK_PERIOD_MS);
       xSemaphoreGive(xSemaphoreSPI);
    }
}
