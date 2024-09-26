#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "sdkconfig.h"



#define ANALOG_PIN_SOIL GPIO_NUM_35  // Soil moisture sensor pin
#define ANALOG_PIN_RAIN GPIO_NUM_34  // Rainfall sensor pin

#ifndef CONFIG_FREERTOS_HZ
#define CONFIG_FREERTOS_HZ 1000
#endif

void init_adc() {
    adc1_config_width(ADC_WIDTH_BIT_12);    
    adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_DB_0); // Soil moisture sensor
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_0); // Rainfall sensor
}

// Function to read and classify soil moisture level
void soil_moisture_task(void *pvParameter) {
    while (1) {
        uint32_t adc_reading = adc1_get_raw(ADC1_CHANNEL_7); 
        
        printf("Soil Moisture ADC Reading: %lu - ", adc_reading);
        if (adc_reading == 0) {
            printf("No Moisture\n");
        } else if (adc_reading <= 3000) {
            printf("Slightly Moist\n");
        } else {
            printf("Very Moist\n");
        }

        vTaskDelay(pdMS_TO_TICKS(3600000)); // Delay 1 hour
    }
}

// Function to read and classify rainfall level
void rainfall_task(void *pvParameter) {
    while (1) {
        uint32_t adc_reading = adc1_get_raw(ADC1_CHANNEL_6);

        printf("Rainfall ADC Reading: %lu - ", adc_reading);
        if (adc_reading < 1000) {
            printf("No Rain\n");
        } else if (adc_reading < 3000) {
            printf("Light Rain\n");
        } else {
            printf("Heavy Rain\n");
        }

        vTaskDelay(pdMS_TO_TICKS(3600000)); // Delay 1 hour
        
    }
}
