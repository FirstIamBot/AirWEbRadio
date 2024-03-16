#include <AiEsp32RotaryEncoder.h>

//********************************     Rotary Encoder    ******************************
#define ROTARY_ENCODER_A_PIN      3  // CLK(А)     синий   25 
#define ROTARY_ENCODER_B_PIN      1  // DT(В)      зелёный 26
#define ROTARY_ENCODER_BUTTON_PIN 13  // SW(Button) фиолетовый
#define ROTARY_ENCODER_VCC_PIN   -1   //
//depending on your encoder - try 1,2 or 4 to get expected behaviour
//#define ROTARY_ENCODER_STEPS 1
//#define ROTARY_ENCODER_STEPS 2
#define ROTARY_ENCODER_STEPS 4



int64_t Encpos;
int8_t Button;
int8_t State;
int8_t Mode;

int8_t Current_pos;
int8_t Select_pos;

AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(
                    ROTARY_ENCODER_A_PIN, \
                    ROTARY_ENCODER_B_PIN, \
                    ROTARY_ENCODER_BUTTON_PIN, \
                    ROTARY_ENCODER_VCC_PIN, \
                    ROTARY_ENCODER_STEPS);
//***********************************************************************
void IRAM_ATTR readEncoderISR()
{
  rotaryEncoder.readEncoder_ISR();
}

void rotary_loop(void);
void rotary_onButtonClick(void);
//***********************************************************************


void Task_Encoder(void *pvParameters) // This is a task.
{
  (void)pvParameters;

    //****************************    rotaryEncoder    *********************
  rotaryEncoder.begin();
  rotaryEncoder.setup(readEncoderISR);
  //rotaryEncoder.setup([]{rotaryEncoder.readEncoder_ISR();}); // установка прерываний для Энкодера
  //optionally we can set boundaries and if values should cycle or not
  bool circleValues = false;
  rotaryEncoder.setBoundaries(0, 400, circleValues);// Установка границы от текущей темрературы до максимальной
  rotaryEncoder.setAcceleration(150); //or set the value - larger number = more accelearation; 0 or 1 means disabled acceleration
  //rotaryEncoder.disableAcceleration(); //acceleration is now enabled by default - disable if you dont need it
  rotaryEncoder.setEncoderValue(25); // init start value rotary encoder
  Serial.println("RotaryEncoder init");
   
  while (1) // A Task shall never return or exit.
  {
    rotary_loop();
    vTaskDelay(100);
  }
}
//***********************************************************************
//***********************************************************************
//***********************************************************************
void rotary_loop(void)
{
	//dont print anything unless value changed
	if(rotaryEncoder.encoderChanged())
	{
     Serial.print("Encoder Rotary = "); Serial.println(rotaryEncoder.readEncoder());
	}
	if(rotaryEncoder.isEncoderButtonClicked())
	{
		rotary_onButtonClick();
	}
}

void rotary_onButtonClick(void)
{
    Serial.print("Encoder Button Clicket time = ");
    Serial.println(rotaryEncoder.isEncoderButtonType());
    
}