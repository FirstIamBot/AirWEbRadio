
#include "Task_radio.h"
#include <FS.h>
#include "EEPROM.h"
#include "SPIFFS.h" // ESP32 only
#include <LittleFS.h>
#include <Wire.h>
#include "SI4735.h"
//#include "patch_init.h"    // SSB patch for whole SSBRX initialization string
#include "patch_full.h"    // SSB patch for whole SSBRX full download
const uint16_t size_content = sizeof ssb_patch_content; // see ssb_patch_content in patch_full.h or patch_init.h

#include "custom.h"

#define EuroAsiabandplan

/************************************************************************************************
    Define  
*************************************************************************************************/

#define ESP32_I2C_SDA    21  // I2C bus pin on ESP32
#define ESP32_I2C_SCL    22  // I2C bus pin on ESP32

#define LW_BAND_TYPE 0
#define MW_BAND_TYPE 1
#define SW_BAND_TYPE 2
#define FM_BAND_TYPE 3

#define offsetEEPROM       0x20
#define EEPROM_SIZE        265

#define AUDIO_MUTE       27

#define AM          3
#define FM          0
#define LSB         1
#define USB         2
#define CW          4

/************************************************************************************************
    Define prototip
*************************************************************************************************/
void saveConfig(void);
void SetConfig(void);
void SaveInEeprom (void* arg);
void printConfig(void);
void loadConfig(void);
void EraseConfig(void);
//===========================================++++=== Bandwidth AM, SSB, FM     ==================================
const char *  bandwidthSSB[] = {
    "0.5",
    "1.0",
    "1.2",
    "2.2",
    "3.0",
    "4.0"};

const char *  bandwidthAM[] = {
    "1.0",
    "1.8",
    "2.0",
    "2.5",
    "3.0",
    "4.0",
    "6.0"};

const char * bandwidthFM[] = {
    "AUT", // Automatic - default
    "110", // Force wide (110 kHz) channel filter.
    " 84",
    " 60",
    " 40"};
//======================================================= End Bandwidth AM & FM & SSB ===========================
//======================================================= End Step AM & FM & SSB =================================
typedef struct
{
  uint8_t idx;      // SI473X device bandwidth index
  const char *desc; // bandwidth description
} Step;

Step stepAM[] = {
  {1, "1"},
  {5, "5"},
  {8, "8"},
  {10, "10"},
};
Step stepFM[] = {
  {1, "10"},
  {5, "50"},
  {10,"100"},
  {20,"200"},
};
//======================================================= THE Step Definitions     ==============================

//======================================================= THE Band Definitions     ==============================
typedef struct // Band data
{
  const char *bandName; // Bandname
  uint8_t  bandType;    // Band type (FM, MW or SW)
  uint16_t prefmod;     // Pref. modulation
  uint16_t minimumFreq; // Minimum frequency of the band
  uint16_t maximumFreq; // maximum frequency of the band
  uint16_t currentFreq; // Default frequency or current frequency
  uint8_t  currentStep; // Default step (increment and decrement)
  int          lastBFO; // Last BFO per band
  int      lastmanuBFO; // Last Manual BFO per band using X-Tal

} Band;

//   Band table
Band band[] = {
#ifdef EuroAsiabandplan
  {   "FM" , FM_BAND_TYPE,  FM,  6400, 10800, 10260, 10, 0, 0}, //  FM          0
  {   "LW" , LW_BAND_TYPE,  AM,   130,   279,   198,  9, 0, 0}, //  LW          1
  {   "MW" , MW_BAND_TYPE,  AM,   522,  1701,  1395,  9, 0, 0}, //  MW          2
  {"BEACON", LW_BAND_TYPE,  AM,   280,   470,   284,  1, 0, 0}, // Ham  600M    3
  { "630M" , SW_BAND_TYPE, LSB,   472,   479,   475,  1, 0, 0}, // Ham  630M    4
  { "160M" , SW_BAND_TYPE, LSB,  1800,  1910,  1899,  1, 0, 0}, // Ham  160M    5
  { "120M" , SW_BAND_TYPE,  AM,  2300,  2495,  2400,  5, 0, 0}, //      120M    6
  {  "90M" , SW_BAND_TYPE,  AM,  3200,  3400,  3300,  5, 0, 0}, //       90M    7
  {  "80M" , SW_BAND_TYPE, LSB,  3500,  3800,  3630,  1, 0, 0}, // Ham   80M    8
  {  "75M" , SW_BAND_TYPE,  AM,  3900,  4000,  3950,  5, 0, 0}, //       75M    9
  {  "60M" , SW_BAND_TYPE, USB,  5330,  5410,  5375,  1, 0, 0}, // Ham   60M   10
  {  "49M" , SW_BAND_TYPE,  AM,  5900,  6200,  6000,  5, 0, 0}, //       49M   11
  {  "40M" , SW_BAND_TYPE, LSB,  7000,  7200,  7185,  1, 0, 0}, // Ham   40M   12
  {  "41M" , SW_BAND_TYPE,  AM,  7200,  7450,  7210,  5, 0, 0}, //       41M   13
  {  "31M" , SW_BAND_TYPE,  AM,  9400,  9900,  9600,  5, 0, 0}, //       31M   14
  {  "30M" , SW_BAND_TYPE, USB, 10100, 10150, 10125,  1, 0, 0}, // Ham   30M   15
  {  "25M" , SW_BAND_TYPE,  AM, 11600, 12100, 11700,  5, 0, 0}, //       25M   16
  {  "22M" , SW_BAND_TYPE,  AM, 13570, 13870, 13700,  5, 0, 0}, //       22M   17
  {  "20M" , SW_BAND_TYPE, USB, 14000, 14350, 14250,  1, 0, 0}, // Ham   20M   18
  {  "19M" , SW_BAND_TYPE,  AM, 15100, 15830, 15700,  5, 0, 0}, //       19M   19
  {  "17M" , SW_BAND_TYPE, USB, 18068, 18168, 18100,  1, 0, 0}, // Ham   17M   20
  {  "16M" , SW_BAND_TYPE,  AM, 17480, 17900, 17600,  5, 0, 0}, //       16M   21
  {  "15M" , SW_BAND_TYPE,  AM, 18900, 19020, 18950,  5, 0, 0}, //       15M   22
  {  "15M" , SW_BAND_TYPE, USB, 21000, 21450, 21350,  1, 0, 0}, // Ham   15M   23
  {  "13M" , SW_BAND_TYPE,  AM, 21450, 21850, 21500,  5, 0, 0}, //       13M   24
  {  "12M" , SW_BAND_TYPE, USB, 24890, 24990, 24940,  1, 0, 0}, // Ham   12M   25
  {  "11M" , SW_BAND_TYPE,  AM, 25670, 26100, 25800,  5, 0, 0}, //       11M   26
  {   "CB" , SW_BAND_TYPE,  AM, 26200, 27990, 27200,  1, 0, 0}, // CB band     27
  {  "10M" , SW_BAND_TYPE, USB, 28000, 30000, 28500,  1, 0, 0}, // Ham   10M   28
  {   "SW" , SW_BAND_TYPE,  AM,  1730, 30000, 15500,  5, 0, 0}  // Whole SW    29
#endif

#ifdef    NandSAmericanbandplan
  {   "FM" , FM_BAND_TYPE,  FM,  8750, 10800,  8930, 10, 0, 0}, //  FM          0
  {   "LW" , LW_BAND_TYPE,  AM,   130,   279,   198,  9, 0, 0}, //  LW          1
  {   "MW" , MW_BAND_TYPE,  AM,   530,  1700,  1390, 10, 0, 0}, //  MW          2
  {"BEACON", LW_BAND_TYPE,  AM,   280,   470,   284,  1, 0, 0}, // Ham  600M    3
  { "630M" , SW_BAND_TYPE, LSB,   472,   479,   475,  1, 0, 0}, // Ham  630M    4
  { "160M" , SW_BAND_TYPE, LSB,  1800,  2000,  1899,  1, 0, 0}, // Ham  160M    5
  { "120M" , SW_BAND_TYPE,  AM,  2300,  2495,  2400,  5, 0, 0}, //      120M    6
  {  "90M" , SW_BAND_TYPE,  AM,  3200,  3400,  3300,  5, 0, 0}, //       90M    7
  {  "80M" , SW_BAND_TYPE, LSB,  3500,  4000,  3630,  1, 0, 0}, // Ham   80M    8
  {  "75M" , SW_BAND_TYPE,  AM,  3900,  4000,  3950,  5, 0, 0}, //       75M    9
  {  "60M" , SW_BAND_TYPE, USB,  5330,  5410,  5375,  1, 0, 0}, // Ham   60M   10
  {  "49M" , SW_BAND_TYPE,  AM,  5900,  6200,  6000,  5, 0, 0}, //       49M   11
  {  "40M" , SW_BAND_TYPE, LSB,  7000,  7300,  7185,  1, 0, 0}, // Ham   40M   12
  {  "41M" , SW_BAND_TYPE,  AM,  7200,  7450,  7210,  5, 0, 0}, //       41M   13
  {  "31M" , SW_BAND_TYPE,  AM,  9400,  9900,  9600,  5, 0, 0}, //       31M   14
  {  "30M" , SW_BAND_TYPE, USB, 10100, 10150, 10125,  1, 0, 0}, // Ham   30M   15
  {  "25M" , SW_BAND_TYPE,  AM, 11600, 12100, 11700,  5, 0, 0}, //       25M   16
  {  "22M" , SW_BAND_TYPE,  AM, 13570, 13870, 13700,  5, 0, 0}, //       22M   17
  {  "20M" , SW_BAND_TYPE, USB, 14000, 14350, 14250,  1, 0, 0}, // Ham   20M   18
  {  "19M" , SW_BAND_TYPE,  AM, 15100, 15830, 15700,  5, 0, 0}, //       19M   19
  {  "17M" , SW_BAND_TYPE, USB, 18068, 18168, 18100,  1, 0, 0}, // Ham   17M   20
  {  "16M" , SW_BAND_TYPE,  AM, 17480, 17900, 17600,  5, 0, 0}, //       16M   21
  {  "15M" , SW_BAND_TYPE,  AM, 18900, 19020, 18950,  5, 0, 0}, //       15M   22
  {  "15M" , SW_BAND_TYPE, USB, 21000, 21450, 21350,  1, 0, 0}, // Ham   15M   23
  {  "13M" , SW_BAND_TYPE,  AM, 21450, 21850, 21500,  5, 0, 0}, //       13M   24
  {  "12M" , SW_BAND_TYPE, USB, 24890, 24990, 24940,  1, 0, 0}, // Ham   12M   25
  {  "11M" , SW_BAND_TYPE,  AM, 25670, 26100, 25800,  5, 0, 0}, //       11M   26
  {   "CB" , SW_BAND_TYPE,  AM, 26200, 27990, 27200,  1, 0, 0}, // CB band     27
  {  "10M" , SW_BAND_TYPE, USB, 28000, 29700, 28500,  1, 0, 0}, // Ham   10M   28
  {   "SW" , SW_BAND_TYPE,  AM,  1730, 30000, 15500,  5, 0, 0}  // Whole SW    29
#endif
};
//=============================================================================================================


#define AMPLFLT_on 0
#define AMPLFLT_off 1

extern QueueHandle_t xQueueGUItoSI4735;
extern QueueHandle_t xQueueSI4735toGUI;

bool writingEeprom  = false;

uint8_t volume = 80;

uint8_t currentStep = 10; // Default step (increment and decrement)
uint16_t currentRSSI = 0;
uint16_t currentSNR = 0;
uint8_t currentMod = 0;
uint8_t currentBandType = FM_BAND_TYPE ; 

uint8_t BandWidthFM = 0;
uint8_t BandWidthAM = 0;
uint8_t BandWidthSSB = 0;

uint8_t stereo = 0;

int16_t si4735Addr ;
//******************************************************************************
SI4735 si4735;          // Init resiver SI4735
#define RESET_PIN 12
//=============================================================================================================
uint8_t bandIdx;
uint8_t stepIdx;
uint8_t bwIdx;

uint16_t previousFrequency;
uint16_t currentFrequency;
uint8_t currentBFOStep     = 25;

uint8_t disableAgc = 0;     // 0 = AGC enabled; 1 = AGC disabled

uint8_t currentAGCgain     =  18;
uint8_t previousAGCgain    =  1;
uint8_t currentAGCgainStep =  1;
uint8_t AGCgainOnOff  = 0 ; //  (0 = AGC enabled; 1 = AGC disabled);
uint8_t MaxAGCgain;
uint8_t MaxAGCgainFM       = 26;  //0 = Minimum attenuation (max gain)
                                  //36 - Maximum attenuation (min gain)
uint8_t MaxAGCgainAM       = 37;
uint8_t MinAGCgain         =  1;


uint8_t currentVOL         =  60; //0 - min, 63 - max
uint8_t previousVOL        =  0;
uint8_t currentVOLStep     =  1;

uint8_t FirmwarePN ;
uint8_t FirmwareFWMAJOR;
uint8_t FirmwareFWMINOR;

uint8_t ssbLoaded;

Data_GUI_Air xReceivedGUIfromSI4735;
Data_Air_GUI xTransmitSI4735todGUI;  
//=============================================================================================================
struct StoreStruct {
  byte     chkDigit;
  byte     bandIdx;
  uint16_t Freq;
  uint8_t  currentMode;
  uint8_t  bwIdxSSB;
  uint8_t  bwIdxAM;
  uint8_t  bwIdxFM;
  uint8_t  ssIdxMW;
  uint8_t  ssIdxAM;
  uint8_t  ssIdxFM;
  int      currentBFO;
  int      currentBFOmanu;
  uint8_t  currentAGCAtt;
  uint8_t  currentVOL;
  uint8_t  currentBFOStep;
  uint8_t  RDS;
  unsigned long FreqExtCristal;
  uint16_t currentBrightness;
  uint8_t  currentAGCgain;
  float calibratvalSI5351;
  int  BFOLW;
  int  BFOMW;
  int  BFO600M;
  int  BFO630M;
  int  BFO160M;
  int  BFO120M;
  int  BFO90M;
  int  BFO80M;
  int  BFO75M;
  int  BFO60M;
  int  BFO49M;
  int  BFO40M;
  int  BFO41M;
  int  BFO31M;
  int  BFO30M;
  int  BFO25M;
  int  BFO22M;
  int  BFO20M;
  int  BFO19M;
  int  BFO17M;
  int  BFO16M;
  int  BFO15M;
  int  BFO15H;
  int  BFO13M;
  int  BFO12M;
  int  BFO11M;
  int  BFOCB;
  int  BFO10M;
  int  BFOSW;
};

StoreStruct storage = {
  '#',  //First time check
  0,  //bandIdx
  8930,  //Freq
  0,  //mode
  1,  //bwIdxSSB
  1,  //bwIdxAM
  0,  //bwIdxFM
  0,  //ssIdxMW
  5,  //ssIdxAM
  10,  //ssIdxFM
  0,  //currentBFO
  0,  //currentBFOmanu
  2,  //currentAGCAtt
  45,  //currentVOL
  25,  //currentBFOStep
  1,  //RDS
  3276800,  //FreqExtCristal
  20,  //currentBrightness
  1,  //currentAGCgain
  0,  //calibratvalSI5351
  0,  //BFOLW;
  0,  //BFOMW
  0,  //BFO600M
  0,  //BFO630M
  0,  //BFO160M
  0,  //BFO120M
  0,  //BFO90M
  0,  //BFO80M
  0,  //BFO75M
  0,  //BFO60M
  0,  //BFO49M
  0,  //BFO40M
  0,  //BFO41M
  0,  //BFO31M
  0,  //BFO30M
  0,  //BFO25M
  0,  //BFO22M
  0,  //BFO20M
  0,  //BFO19M
  0,  //BFO17M
  0,  //BFO16M
  0,  //BFO15M
  0,  //BFO15H
  0,  //BFO13M
  0,  //BFO12M
  0,  //BFO11M
  0,  //BFOCB
  0,  //BFO10M
  0   //BFOSW
};

//#############################################################################################################
void showStatus()
{
	si4735.getStatus();
	si4735.getCurrentReceivedSignalQuality();
	Serial.print("You are tuned on ");
    currentFrequency = si4735.getFrequency();
	if (si4735.isCurrentTuneFM())
	{
		Serial.print(String(currentFrequency / 100.0, 2));
		Serial.print("MHz ");
    stereo = si4735.getCurrentPilot(); //(si4735.getCurrentPilot()) ? "STEREO" : "MONO"
		Serial.print("Audio Out = "); Serial.println(stereo ? "stereo" : "mono");
	}
	else
	{
		Serial.print(currentFrequency);
		Serial.print(" kHz");
	}
  currentSNR = si4735.getCurrentSNR();
	Serial.print(" [SNR:");
	Serial.print(currentSNR);
	Serial.print("dB  ");

  currentRSSI = si4735.getCurrentRSSI();
	Serial.print(" Signal:");
	Serial.print(currentRSSI);
	Serial.println("dBuV]");
	//si4735Addr = si4735.getDeviceI2CAddress(RESET_PIN);
  Serial.print("si4735Addr = ");Serial.println(si4735Addr, HEX);

  FirmwarePN = si4735.getFirmwarePN();
  Serial.print("FirmwarePN = ");Serial.println(FirmwarePN);
  FirmwareFWMAJOR = si4735.getFirmwareFWMAJOR();
  Serial.print("FirmwareFWMAJOR = ");Serial.println(FirmwareFWMAJOR);
  FirmwareFWMINOR = si4735.getFirmwareFWMINOR();
  Serial.print("FirmwareFWMINOR = ");Serial.println(FirmwareFWMINOR);
  currentVOL = si4735.getVolume();
  Serial.print("currentVOL = ");Serial.println(currentVOL);

}

void loadSSB() {
  si4735.setI2CFastModeCustom(400000); // You can try rx.setI2CFastModeCustom(700000); or greater value
  si4735.loadPatch(ssb_patch_content, size_content, BandWidthSSB); // 
  si4735.setI2CFastModeCustom(100000);
}
// Send Status on GUI
void sendStatus()
{
  char strfreq[10];
  char strrssi[5];
  
  uint8_t n = 5, d = 3;

  si4735.getStatus();
	si4735.getCurrentReceivedSignalQuality();
  currentFrequency = si4735.getFrequency();

	if (si4735.isCurrentTuneFM())
	{
    if (currentFrequency < 10000)
    {
      n = 4;
      d = 2;
    }
    xTransmitSI4735todGUI.ucFreq = currentFrequency;
    si4735.convertToChar(currentFrequency, strfreq, n, d, '.',true);
    xTransmitSI4735todGUI.vcFreqRange = "MHz";
    stereo = si4735.getCurrentPilot();
    if( stereo == 0 )
    {
      xTransmitSI4735todGUI.vcStereoMono = " mono ";
    } 
    else
    {
      xTransmitSI4735todGUI.vcStereoMono = "stereo";
    }
	}
	else
	{
    if (currentBandType == MW_BAND_TYPE || currentBandType == LW_BAND_TYPE || currentBandType == SW_BAND_TYPE)
    {
      si4735.convertToChar(currentFrequency, strfreq, 5, 0, '.');
    }
    else
    {
      si4735.convertToChar(currentFrequency, strfreq, 5, 2, '.');
    }
    xTransmitSI4735todGUI.ucFreq = currentFrequency;
    xTransmitSI4735todGUI.vcFreqRange = "KHz";
    xTransmitSI4735todGUI.vcStereoMono = "      ";
  }
  currentSNR = si4735.getCurrentRSSI();
  xTransmitSI4735todGUI.ucSNR = currentSNR;
  currentSNR = si4735.getCurrentRSSI();
  xTransmitSI4735todGUI.ucRSSI = currentRSSI;

  if (currentBandType == MW_BAND_TYPE || currentBandType == LW_BAND_TYPE || currentBandType == SW_BAND_TYPE  )
  { 
    xTransmitSI4735todGUI.vcStep = (char *)stepAM[currentStep].desc;  
    if(currentMod == 0) // AM (AM modulation) mode
    {
      xTransmitSI4735todGUI.vcBW = (char * )bandwidthAM[BandWidthAM];
    }
    else // SSB (LSB, USB modulation) mode
    {
       xTransmitSI4735todGUI.vcBW = (char * )bandwidthSSB[BandWidthSSB];
    }
  }
  else if(currentBandType == FM_BAND_TYPE )
  {
    xTransmitSI4735todGUI.vcBW = (char *)bandwidthFM[BandWidthFM];
    xTransmitSI4735todGUI.vcStep =  (char *)stepFM[currentStep].desc; 
  }
  xTransmitSI4735todGUI.ucBand = currentBandType;
  xTransmitSI4735todGUI.ucslider_vol = currentVOL;
  xTransmitSI4735todGUI.eDataDescription = eFreq;
  xTransmitSI4735todGUI.State = true;
}
//###############################################################################################################
void initRadio(void)
{
    digitalWrite(RESET_PIN, HIGH);

    // The line below may be necessary to setup I2C pins on ESP32
    //Wire.begin(ESP32_I2C_SDA, ESP32_I2C_SCL);
    si4735Addr = si4735.getDeviceI2CAddress(RESET_PIN);
    si4735.setDeviceI2CAddress(0);
    delay(1500); 
    si4735.setRefClock(32768);
    si4735.setRefClockPrescaler(1);   // will work with 32768 Hz
    si4735.setup(RESET_PIN, -1, POWER_UP_FM, SI473X_ANALOG_AUDIO, XOSCEN_RCLK); // Start in FM
    delay(500);
    si4735.setVolume(currentVOL);
    si4735.setSeekFmSpacing(10);
    si4735.setSeekFmLimits(8750, 10800);
    si4735.setSeekAmRssiThreshold(50);
    si4735.setSeekAmSrnThreshold(20);
    si4735.setSeekFmRssiThreshold(5);
    si4735.setSeekFmSrnThreshold(5);
    // Starts defaul radio function and band (FM; from 84 to 108 MHz; 103.9 MHz; step 100kHz) 
    currentStep = 0;
    si4735.setTuneFrequencyAntennaCapacitor(0); //0    
    si4735.setFM(8400, 10800, 10360, stepFM[currentStep].idx);
    //currentAGCgain = MaxAGCgainFM;
    //si4735.setAutomaticGainControl(1, currentAGCgain); //MaxAGCgainFM 
    si4735.setFmBandwidth(0);
    si4735.RdsInit();
    si4735.setRdsConfig(1, 2, 2, 2, 2);
    Serial.println("Init Si4735 !");
    showStatus();
}

void Task_Radio(void *pvParameters)
{   
    (void)pvParameters;
    BaseType_t xStatus;

    uint16_t XZ; //Так для пробы
    static uint16_t lastXZ; //Так для пробы

    Serial.println("Start Task Radio.");  
    initRadio();
  
    while(1)
    {       
      xStatus = xQueueReceive( xQueueGUItoSI4735, &xReceivedGUIfromSI4735, 1000);
      //xStatus = xQueueReceive( xQueueGUItoSI4735, &xReceivedGUIfromSI4735, portMAX_DELAY);
      if( xStatus == pdPASS )
      {
        switch (xReceivedGUIfromSI4735.eDataDescription)
        {
          case ebandIDx:
            if(xReceivedGUIfromSI4735.ucValue == LW_BAND_TYPE){
              si4735.setup(RESET_PIN, -1, POWER_UP_AM, SI473X_ANALOG_AUDIO, XOSCEN_RCLK); // Start in AM
              si4735.setTuneFrequencyAntennaCapacitor(0);
              si4735.setAM(130, 279, 198, stepFM[currentStep].idx);
              si4735.setBandwidth(0, AMPLFLT_on);
              si4735.setVolume(currentVOL);
              currentBandType = LW_BAND_TYPE;
              Serial.println("LW_BAND_TYPE");
            }
            if(xReceivedGUIfromSI4735.ucValue == MW_BAND_TYPE){
              si4735.setup(RESET_PIN, -1, POWER_UP_AM, SI473X_ANALOG_AUDIO, XOSCEN_RCLK); // Start in AM
              si4735.setTuneFrequencyAntennaCapacitor(0);
              si4735.setAM(520, 1750, 550, stepFM[currentStep].idx);
              si4735.setBandwidth(0, AMPLFLT_on);
              si4735.setVolume(currentVOL);
              currentBandType = MW_BAND_TYPE;
              Serial.println("MW_BAND_TYPE");
            }
            if(xReceivedGUIfromSI4735.ucValue == SW_BAND_TYPE){
              si4735.setup(RESET_PIN, -1, POWER_UP_AM, SI473X_ANALOG_AUDIO, XOSCEN_RCLK); // Start in AM
              si4735.setTuneFrequencyAntennaCapacitor(0);
              si4735.setAM(1730, 30000, 15500, stepFM[currentStep].idx );
              si4735.setBandwidth(0, AMPLFLT_on);
              si4735.setVolume(currentVOL);
              currentBandType = SW_BAND_TYPE;
              Serial.println("SW_BAND_TYPE");
            }
            if(xReceivedGUIfromSI4735.ucValue == FM_BAND_TYPE){
              si4735.setTuneFrequencyAntennaCapacitor(80);//0
              delay(100);
              si4735.setFM(8400, 10800, 10360, stepFM[currentStep].idx);
              si4735.setFMDeEmphasis(1);
              si4735.setVolume(currentVOL);
              currentAGCgain = MaxAGCgainFM;
              si4735.setAutomaticGainControl(disableAgc, currentAGCgain);
              currentBandType = FM_BAND_TYPE;
              si4735.RdsInit();
              si4735.setRdsConfig(1, 2, 2, 2, 2);
              Serial.println("FM_BAND_TYPE");
              }
            break;
          case eModIdx: 
            currentMod = xReceivedGUIfromSI4735.ucValue;
            if(currentMod != 0)
            {
              loadSSB();
              si4735.setFmBandwidth(BandWidthSSB);
            }
            else{
                si4735.setAM(130, 279, 198, stepFM[currentStep].idx);
                si4735.setFmBandwidth(BandWidthAM);
            }
            Serial.print("set Modulation = "); Serial.println(currentMod);
             break;
          case eStepFM:
            currentStep = xReceivedGUIfromSI4735.ucValue; 
            si4735.setFrequencyStep(stepFM[currentStep].idx);
            Serial.print("set Step FM = "); Serial.println(currentStep);
            break;
          case eStepAM:
            currentStep = xReceivedGUIfromSI4735.ucValue; 
            si4735.setFrequencyStep(stepFM[currentStep].idx);
            Serial.print("set Step AM = "); Serial.println(currentStep);
            break;
          case eBandWFM:
            BandWidthFM = xReceivedGUIfromSI4735.ucValue;
            si4735.setFmBandwidth(BandWidthFM);
            Serial.print("set BandWidth FM = "); Serial.println(BandWidthFM);
            break;
          case eBandWAM:
            BandWidthAM = xReceivedGUIfromSI4735.ucValue;
            si4735.setBandwidth(BandWidthAM, AMPLFLT_on);
            Serial.print("set BandWidth AM = "); Serial.println(BandWidthAM);
            break;
          case eBandWSSB:
            BandWidthSSB = xReceivedGUIfromSI4735.ucValue;
            si4735.setFmBandwidth(BandWidthSSB);
            Serial.print("Set BandW SSB = ");Serial.println(BandWidthSSB);  
            break;
          case eStepUP:
            si4735.frequencyUp();
            Serial.println("Set Frequency Up");
            break;
          case eStepDown:
            si4735.frequencyDown();
            Serial.println("Set Frequency Down");
            break;
            case eSeekUP:
            si4735.seekStationUp();
            Serial.println("Seek Station Up");
            break;
          case eSeekDown:
            si4735.seekStationDown();
            Serial.println("Seek Station Down");
            break;
          case eSlider_agc:
            currentAGCgain = xReceivedGUIfromSI4735.ucValue; 
            si4735.setAutomaticGainControl(AGCgainOnOff, currentAGCgain);
            Serial.print("Set AGC = ");Serial.println(currentAGCgain); 
            break;
          case eAGCgain:
            AGCgainOnOff = xReceivedGUIfromSI4735.ucValue; 
            si4735.setAutomaticGainControl(AGCgainOnOff, currentAGCgain);
            Serial.print("AGCgainOnOff = ");Serial.println(AGCgainOnOff); 
            break;
          case eslider_vol:
            currentVOL = xReceivedGUIfromSI4735.ucValue*0.63;       
            si4735.setVolume(currentVOL);
            Serial.print("Set volume = ");Serial.println(currentVOL);   
            break;
          default:
            break;
        }
      }
      else
      {
        // Очередь пуста
        Serial.println("Queue Empty !!!");
      }
      //vTaskDelay(200);
      /*
        Очередь xQueueSI4735toGUI для отравки информации на экран
      */
      //showStatus();
      sendStatus();
      if(xTransmitSI4735todGUI.State == true)
      {
        //if( xQueueSend( xQueueGUItoSI4735, &xTransmitSI4735todGUI, portMAX_DELAY ) != pdPASS )
        if( xQueueSend( xQueueSI4735toGUI, &xTransmitSI4735todGUI, 500 ) != pdPASS ) 
          {
            Serial.println("We not transmit queue xTransmitSI4735todGUI!");
          }
        xTransmitSI4735todGUI.State = false;
      }
    }
}

//=======================================================================================
void SetConfig(void)
{
  if (!EEPROM.begin(EEPROM_SIZE))
  {
    //tft.fillScreen(TFT_BLACK);
    //tft.setCursor(0, 0);
    //tft.println(F("failed to initialise EEPROM"));
    Serial.println(F("failed to initialise EEPROM"));
    while (1);
  }

  if (EEPROM.read(offsetEEPROM) != storage.chkDigit) {
    Serial.println(F("Writing defaults...."));
    saveConfig();
  }
  loadConfig();
  printConfig();

}
//=======================================================================================
void printConfig() {
  Serial.print("Storage = ");
  Serial.println(sizeof(storage));
  if (EEPROM.read(offsetEEPROM) == storage.chkDigit) {
    for (unsigned int t = 0; t < sizeof(storage); t++)
      Serial.write(EEPROM.read(offsetEEPROM + t));
    Serial.println();
  }
}
//=======================================================================================
void SaveInEeprom (void* arg)  {
  while (1) {
 
    for (unsigned int t = 0; t < sizeof(storage); t++) {
      delay(1);
      if (EEPROM.read(offsetEEPROM + t) != *((char*)&storage + t)) {
        delay(1);
        EEPROM.write(offsetEEPROM + t, *((char*)&storage + t));
      }
    }

    writingEeprom = true;
    EEPROM.commit();
    writingEeprom = false;
    vTaskDelay(5000 / portTICK_RATE_MS);
  }

}
//=======================================================================================
void saveConfig(void) {
  delay(10);
  for (unsigned int t = 0; t < sizeof(storage); t++) {
    if (EEPROM.read(offsetEEPROM + t) != *((char*)&storage + t)) {
      EEPROM.write(offsetEEPROM + t, *((char*)&storage + t));
    }
  }
  EEPROM.commit();
}
//=======================================================================================
void loadConfig(void) {
  if (EEPROM.read(offsetEEPROM + 0) == storage.chkDigit) {
    for (unsigned int t = 0; t < sizeof(storage); t++)
      *((char*)&storage + t) = EEPROM.read(offsetEEPROM + t);
    Serial.println("Load config done");
  }
}
//========================================================================================
void EraseConfig(void)
{
    // If you want to reset the eeprom, keep the VOLUME_UP button pressed during statup

  for (unsigned int t = 0; t < sizeof(storage); t++) {
      EEPROM.write(offsetEEPROM + t, 0);
  }
  EEPROM.commit();
  Serial.print("EEPROM RESETED");
  delay(2000);// 3000
}