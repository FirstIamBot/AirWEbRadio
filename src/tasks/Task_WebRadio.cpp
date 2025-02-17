#include "vs1053/VS1053.h"
#include "SampleMp3.h"
//#include <SPI.h>

#define __DEBUG

//********************************  Audio codec VS1053  *****************************
#define VS1053_CS     32  // XCS  34
#define VS1053_DCS    33  // DCS  XDCS     
#define VS1053_DREQ   35  // DREQ DREQ     
//EN    RST      | 
//************ VS1053 define constatant **********************
#define buffLen 1024  // Default bitrate stream 1024,for HD radio bitrate stream 4096

#define WebRadio 0
#define AirRadio 1


uint8_t RadioMode;

uint8_t VOLUME ;      // Volume
uint8_t TONE ;        // Tone bass/treble (4 nibbles)

int bytesread;
int num_station;
uint8_t trimble;
uint8_t mp3buff[buffLen];

extern SemaphoreHandle_t xSemaphoreSPI;

VS1053 player(VS1053_CS, VS1053_DCS, VS1053_DREQ);
void loop_vs1053();
void Task_WebRadio(void *pvParameters) // This is a task.
{
    (void)pvParameters;

    int index = 0;
    //****************************    Web Radio Init    *********************
    VOLUME = 90;      // Default volume
    TONE = 0x51;      // Default tone bass/treble (4 nibbles)
    // ******************** Setup VS1053 audio codec
    RadioMode = AirRadio; //WebRadio  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // initialize SPI
    SPI.begin();
    Serial.println("Start Task WebRadio."); 
    // initialize a player
    player.begin();

    if (RadioMode == AirRadio){ // AirRadio
      player.loadUserPatches(0);
      //player.loadUserPatches(2);
      player.switchToUserMode(0);
      Serial.println("Switched to User mode");
    }
    else{        
      player.loadDefaultVs1053Patches();
      player.switchToMp3Mode(); // optional, some boards require this
      Serial.println("Switched to mp3 mode");
    }
    player.setVolume(VOLUME);
 
    while (1) // A Task shall never return or exit.
    {
      if (RadioMode == AirRadio){
        Serial.println("Playing from Adumix");  
        vTaskDelay(1500);
        //loop_vs1053();
      }
      else{// AirRadio
        loop_vs1053();
      }
    }
}

void loop_vs1053(){
  // Delay 1 tick (assumes FreeRTOS tick is 2000ms
  vTaskDelay(pdMS_TO_TICKS(1500));
  if(xSemaphoreTake( xSemaphoreSPI, portMAX_DELAY ) == pdTRUE){
    Serial.println("Playing sound... ");
    // play mp3 flow each 1s
    player.playChunk(sampleMp3, sizeof(sampleMp3));  
    xSemaphoreGive(xSemaphoreSPI);
  }
   
}