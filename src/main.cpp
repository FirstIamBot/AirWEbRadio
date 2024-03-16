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

/************************************************************************************************
    Define prototipr Task
*************************************************************************************************/
//void Task_Encoder(void *pvParameters);
void Task_WebRadio(void *pvParameters);
void Task_TFT(void *pvParameters);

SemaphoreHandle_t xSemaphoreSPI = NULL;

#if CONFIG_FREERTOS_UNICORE
    static const BaseType_t app_cpu = 0;
#else
    static const BaseType_t app_cpu = 1;
#endif


 
void setup(){
  
    Serial.begin(115200);
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    xSemaphoreSPI = xSemaphoreCreateMutex();
    if( xSemaphoreSPI == NULL )
    {
       Serial.println("Error handle mutex\n");
       esp_restart();
    }
    else{
        Serial.printf("Handle mutex xSemaphoreSPI = %d\n", xSemaphoreSPI);Serial.println("!!!");
    }

    //xTaskCreatePinnedToCore( printValues, "Print ADC Values", 1536,  NULL, 3, NULL, app_cpu );
    //xTaskCreatePinnedToCore( Task_Encoder, " Encoder", 1000,  NULL, 2, NULL, app_cpu );
    xTaskCreatePinnedToCore( Task_TFT, " TFT", 1000*4,  NULL, 2, NULL, app_cpu );
    xTaskCreatePinnedToCore( Task_WebRadio, "Web Radio", 1000*2,  NULL, 2, NULL, app_cpu );
   
    Serial.println("\n*** All Tasks Created ***\n");        // Critical Section

    //xSemaphoreGive(xSemaphoreSPI);

}

void loop() {}
