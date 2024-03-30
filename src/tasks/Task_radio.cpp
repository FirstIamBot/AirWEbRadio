
#include "Task_radio.h"
#include <FS.h>
#include "SPIFFS.h" // ESP32 only
#include <LittleFS.h>
#include <Wire.h>
#include "SI4735.h"
//#include "patch_init.h"    // SSB patch for whole SSBRX initialization string
#include "patch_full.h"    // SSB patch for whole SSBRX full download
const uint16_t size_content = sizeof ssb_patch_content; // see ssb_patch_content in patch_full.h or patch_init.h

#include "custom.h"

#define EuroAsiabandplan



#define ESP32_I2C_SDA    21  // I2C bus pin on ESP32
#define ESP32_I2C_SCL    22  // I2C bus pin on ESP32

#define AUDIO_MUTE       27

#define FM          0
#define LSB         1
#define USB         2
#define AM          3
#define CW          4

#define FM_BAND_TYPE 0
#define MW_BAND_TYPE 1
#define SW_BAND_TYPE 2
#define LW_BAND_TYPE 3

//===========================================++++=== Bandwidth AM, SSB, FM     ===============================+
const char *bandwidthSSB[] = {"0.5",  "1.0","1.2", "2.2", "3.0", "4.0"};
const char *bandwidthAM[]  = {"6.0", "4.0", "3.0", "2.5", "2.0","1.8",  "1.0"};
const char *bandwidthFM[]  = {"AUT", "110", "84", "60", "40"};

typedef struct // Bandwidth AM & SSB & FM
{
  uint16_t BandWidthAM;
  uint16_t BandWidthSSB;
  uint16_t BandWidthFM;
} Bandwidth;

Bandwidth bw[] = {       //  AM    SSB   FM
  { 4 , 4 , 0 },         //  1.0   0.5   Aut
  { 5 , 5 , 1 },         //  1.8   1.0   110
  { 3 , 0 , 2 },         //  2.0   1.2    84
  { 6 , 1 , 3 },         //  2.5   2.2    60
  { 2 , 2 , 4 },         //  3.0   3.0    40
  { 1 , 3 , 0 },         //  4.0   4.0   ---
  { 0 , 0 , 0 }          //  6.0   ---   ---
};

const char *bandModeDesc[] = {"FM ", "LSB", "USB", "AM ", "CW"};
//======================================================= End Bandwidth AM & FM & SSB ===========================
//======================================================= Tunings Steps     ===============================
typedef struct // Tuning steps
{
  uint8_t stepFreq;
  double stepFreqFM;
} Step;

Step sp[] = {
  { 1 , 20 },
  { 5 , 10 },
  { 9 ,  1 },
  { 10,  0 }
};
const char *stepsize[]     = {"1", "5", "9", "10"};
const char *stepsizeFM[]   = {"200", "100", "10"};
//======================================================= End Tunings Steps     ===============================
//======================================================= THE Band Definitions     ============================
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
//  Index 
uint8_t bandIdx;
uint8_t stepIdx;
uint8_t bwIdx;

uint16_t previousFrequency;
uint16_t currentFrequency;
uint8_t currentBFOStep     = 25;
uint8_t currentStepIdx     = 1;

uint8_t currentAGCgain     =  1;
uint8_t previousAGCgain    =  1;
uint8_t currentAGCgainStep =  1;
uint8_t MaxAGCgain;
uint8_t MaxAGCgainFM       = 26;
uint8_t MaxAGCgainAM       = 37;
uint8_t MinAGCgain         =  1;
uint8_t rssi = 0;
uint8_t snr = 0;
uint8_t stereo = 1;
uint8_t volume = 50;

uint8_t currentVOL         =  95;
uint8_t previousVOL        =  0;
uint8_t currentVOLStep     =  1;

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


extern QueueHandle_t xQueueGUItoSI4735;;
int16_t si4735Addr ;
//=============================================================================================================
SI4735 si4735;          // Init resiver SI4735
#define RESET_PIN 12
//=============================================================================================================
//#############################################################################################################
// Show current frequency
void showStatus()
{
	si4735.getStatus();
	si4735.getCurrentReceivedSignalQuality();
	Serial.print("You are tuned on ");
	if (si4735.isCurrentTuneFM())
	{
		//currentFrequency = si4735.getFrequency();
		Serial.print(String(currentFrequency / 100.0, 2));
		Serial.print("MHz ");
		Serial.print((si4735.getCurrentPilot()) ? "STEREO" : "MONO");
	}
	else
	{
		Serial.print(currentFrequency);
		Serial.print("kHz");
	}
	Serial.print(" [SNR:");
	Serial.print(si4735.getCurrentSNR());
	Serial.print("dB");

	Serial.print(" Signal:");
	Serial.print(si4735.getCurrentRSSI());
	Serial.println("dBuV]");
	
	si4735Addr = si4735.getDeviceI2CAddress(RESET_PIN);
    Serial.print("si4735Addr = ");Serial.println(si4735Addr, HEX);
}
//###############################################################################################################
void initRadio(void)
{
	

    digitalWrite(RESET_PIN, HIGH);

    // The line below may be necessary to setup I2C pins on ESP32
    Wire.begin(ESP32_I2C_SDA, ESP32_I2C_SCL);

    delay(500);
    si4735.setup(RESET_PIN, 0);
    // Starts defaul radio function and band (FM; from 84 to 108 MHz; 103.9 MHz; step 100kHz)
    si4735.setFM(8400, 10800, 10360, 10);
    delay(500);
    si4735.setVolume(currentVOL);   
    delay(1500);
    Serial.println("Init Si4735 !");
    currentFrequency = previousFrequency = si4735.getFrequency();

    showStatus();
}

void Task_Radio(void *pvParameters)
{   
  (void)pvParameters;
	BaseType_t xStatus;
	Data_GUI_Air xReceivedGUIfromSI4735;
    
	Serial.println("Start Task Radio.");
	uint16_t XZ; //Так для пробы
	static uint16_t lastXZ; //Так для пробы
  initRadio();
    
    while(1)
    {
		
	xStatus = xQueueReceive( xQueueGUItoSI4735, &xReceivedGUIfromSI4735, 500);
	//xStatus = xQueueReceive( xQueueGUItoSI4735, &xReceivedGUIfromSI4735, portMAX_DELAY);
	if( xStatus == pdPASS )
		{
			switch (xReceivedGUIfromSI4735.eDataDescription)
			{
				case ebandIDx:
					XZ = xReceivedGUIfromSI4735.ucValue;
					break;
				case eModIdx:
					// 
					XZ = xReceivedGUIfromSI4735.ucValue;
					break;
				case eStepFM:
					// 
					XZ = xReceivedGUIfromSI4735.ucValue;
					break;
				case eStepAM:
					// 
					XZ = xReceivedGUIfromSI4735.ucValue;
					break;
				case eBandWFM:
					// 
					XZ = xReceivedGUIfromSI4735.ucValue;
					break;
				case eBandWAM:
					// 
					XZ = xReceivedGUIfromSI4735.ucValue;
					break;
				case eBandWSSB:
					// 
					XZ = xReceivedGUIfromSI4735.ucValue;
					break;
        case eStepUP:
					// 
					XZ = xReceivedGUIfromSI4735.ucValue;
					break;
        case eStepDown:
					// 
					XZ = xReceivedGUIfromSI4735.ucValue;
					break;
        case eslider_vol:
					// 
					XZ = xReceivedGUIfromSI4735.ucValue;
					break;
			default:
				break;
			}
			Serial.print(xReceivedGUIfromSI4735.eDataDescription);Serial.print(" = ");Serial.println(XZ);
			if(lastXZ != XZ)
			{
				lastXZ == XZ;
				XZ = 0;
				showStatus();
			}
			}
		else
		{
			// Очередь пуста
			Serial.println("Queue Empty !!!");
		}
    	//vTaskDelay(200);
    }
}