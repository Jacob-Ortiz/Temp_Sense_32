
#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


#include "ADCsense.h"
#include "uartComms.h"

void app_main()
{
    initUART(); // Initializes the UART communication pins
    init_adc();  // Initialize ADC data for the analog sensors 

 

    while(1)
    {
   // Create tasks to read and classify sensor levels
    xTaskCreate(soil_moisture_task, "soil_moisture_task", 2048, NULL, 5, NULL);
    xTaskCreate(rainfall_task, "rainfall_task", 2048, NULL, 5, NULL);

     const char* message = ;   // Define the message to be sent

        
    sendData(message);  // Send the message over UART using command from function created
    vTaskDelay(3600000 / portTICK_PERIOD_MS);     // Delay the task for 10 seconds

    }


 
}

