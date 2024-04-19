/******************************    VS1053   ***************************************
http://andrew25kir.blogspot.com/2017/10/karadio-esp32.html
      Итак,  если вы используете VS1053, то соединения такие:
      VS1053----ESP32 (номера GPIO)
      DREQ----- GPIO_NUM_34       ----------------------
      XDCS----- GPIO_NUM_33       | VS1053  |  ESP32   |
      XCS-----  GPIO_NUM_32       ----------------------
      RST-----  GPIO_NUM_12       |   SCK   |   IO18   |
                                  |   MISO  |   IO19   |
      CLK-----  GPIO_NUM_18       |   MOSI  |   IO23   |
      MISO----- GPIO_NUM_19       |   XRST  |   EN     |
      MOSI----- GPIO_NUM_23       |   CS    |   IO5    |
                                  |   DCS   |   IO16   |
                                  |   DREQ  |   34(IO4)|
                                  |   5V    |   5V     |
                                  |   GND   |   GND    |
                                  ----------------------
  |------------|------------------|------------|------------|------------|------------|
  |Display 2.8 |      ESP32       |   Si4735   |  Encoder   |  Beeper    |  VS1053    |
  |  ILI9341   |                  |            |            |            |            |        
  |------------|------------------|------------|------------|------------|------------|
  |   Vcc      |     3V3     | 01 |    Vcc     |            |            |            |        
  |   GND      |     GND     | 02 |    GND     |     2,4    |            |            |        
  |   CS       |     15      | 03 |            |            |            |            |         
  |   Reset    |      4      | 04 |            |            |            |            |         
  |   D/C      |      2      | 05 |            |            |            |            | 
  |   SDI(MOSI)|     23      | 06 |            |            |            |            |         
  |   SCK      |     18      | 07 |            |            |            |            |         
  |   LED Coll.|     3V3     | 08 |            |            |            |            |         
  |   SDO(MIS) |     19      | 09 |            |            |            |            | 
  |   T_CLK    |     18      | 10 |            |            |            |     CLK    | 
  |   T_CS     |      5      | 11 |            |            |            |            |
  | T_DIN(MOSI)|     23      | 12 |            |            |            |    MOSI    |
  |   T_DO     |     19      | 13 |            |            |            |    MISO    |
  |   T_IRQ    |             |    |            |            |            |            | 
  |            |     12      | RST|    15      |            |            |            |
  |            |     21      | SDA|    18      |            |            |            |
  |            |     22      | SCL|    17      |            |            |            |
  |            |      1      |    |            |      1     |            |            |
  |            |      3      |    |            |      3     |            |            |
  |            |     13      |    |            |      5     |            |            |
  |            |     17      |    |            |            |            |   DREQ     |
  |            |     33      |    |            |            |            |   XDCS     |
  |            |     32      |    |            |            |            |   XCS      |
  |            |     EN      |    |            |            |            |   RST      |
  |------------|-------------|----|------------|------------|------------|------------|
  Library TFT_eSPI you may download from here     : https://github.com/Bodmer/TFT_eSPI
  Library Rotary is provided with the program
  Library SI4735 you may download from here       : https://github.com/pu2clr/SI4735
***************************************************************************************/
#include <Arduino.h>
#include "SPI.h"
#include <FS.h>

#include "SPIFFS.h" // ESP32 only
#include <LittleFS.h>
#include <Wire.h>
#include <WiFi.h>

#include "printvavlue.h"

#include <TFT_eSPI.h> // Hardware-specific library
#include <TFT_eWidget.h>    
//#include "Free_Fonts.h"
#include "Task_TFT.h"
#include "Task_radio.h"
#include "gui/gui.h"
/************************************************************************************************
    Define  
*************************************************************************************************/

/************************************************************************************************
    Define prototip Task
*************************************************************************************************/
//void Task_Encoder(void *pvParameters);
void Task_WebRadio(void *pvParameters);
void Task_TFT(void *pvParameters);
void Task_Radio(void *pvParameters);

// Define Semaphore
SemaphoreHandle_t xSemaphoreSPI = NULL;
// Define Queue
QueueHandle_t xQueueGUItoSI4735;
QueueHandle_t xQueueSI4735toGUI;
/************************************************************************************************
 * 
*************************************************************************************************/

#if CONFIG_FREERTOS_UNICORE
    static const BaseType_t app_cpu = 0;
#else
    static const BaseType_t app_cpu = 1;
#endif


 
void setup(){
  
    Serial.begin(115200);
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    xSemaphoreSPI = xSemaphoreCreateMutex();
    /* Создаем очереди на 5 элементов. */
    xQueueGUItoSI4735 = xQueueCreate( 5, sizeof( Data_GUI_Air ) );
    xQueueSI4735toGUI = xQueueCreate( 5, sizeof( Data_Air_GUI ) );

    if( xSemaphoreSPI == NULL )
    {
       Serial.println("Error handle mutex\n");
       esp_restart();
    }
    else{
        Serial.printf("Handle mutex xSemaphoreSPI = %d\n", xSemaphoreSPI);Serial.println("!!!");
    }

	if( xQueueGUItoSI4735 != NULL && xQueueSI4735toGUI != NULL )
	{
        xTaskCreatePinnedToCore( Task_WebRadio, "Web Radio", 1000*2,  NULL, 2, NULL, app_cpu );
        xTaskCreatePinnedToCore( Task_TFT, " TFT", 1000*4,  NULL, 2, NULL, app_cpu );
        xTaskCreatePinnedToCore( Task_Radio, "Web Radio", 1000*2,  NULL, 2, NULL, app_cpu );
		vTaskStartScheduler();
	}
    
    Serial.println("\n*** All Tasks Created and Queue  ***\n");        // Critical Section

}


void loop() {}



