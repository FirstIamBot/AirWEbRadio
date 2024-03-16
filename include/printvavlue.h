
volatile uint16_t someValue;                         // volatile: value can chage outside currently executing task (Inside the ISR)
SemaphoreHandle_t binSemaphore = NULL;               // Declare global Binary Semaphore

void printValues(void *param)
{
    for (;;)
    {
        xSemaphoreTake(binSemaphore, portMAX_DELAY);        // Wait for semaphore from ISR indefinitely
        Serial.print(someValue);
        Serial.print("  ");
    }
}