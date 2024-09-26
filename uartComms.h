//UART communications design and knowledge came from both ESPRESSIF IDF website and tutorial from https://www.youtube.com/watch?v=15zXAhsVx0k&t=355s 
//Basic header (GPIO) found on Espressif IDF website : https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/gpio.html
//UART Initialization and commands: https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/uart.html


#include "freertos/FreeRTOS.h"    // FreeRTOS includes for multitasking support needed for Sensors and this
#include "freertos/task.h"        // FreeRTOS task management, allowing us to create tasks (like loops)
#include "driver/uart.h"          // UART driver, used to set up UART communication for projectt
#include "driver/gpio.h"          // GPIO driver, allowing us to control input/output pins
#include "string.h"               // Standard C string functions, we use for string manipulations
#include "esp_mac.h"              // Allows use of MAC functions, also supports certain UART operations(Solved errors)

#define TXD_PIN (GPIO_NUM_2)      // Defines TX pin (GPIO 2 to transmit data to the XBee RX pin
#define RXD_PIN (GPIO_NUM_15)     // Defines RX pin (GPIO 15) to receive data from the XBee TX pin
#define UART_NUM UART_NUM_2       // Specifies UART port number 2 for communication

// Function to initialize UART communication
void initUART() {
    const uart_config_t uart_config = {
        .baud_rate = 9600,                  // We set the baud rate to 9600 bits per second (This is the standard for the ZIGBEE radio)
        .data_bits = UART_DATA_8_BITS,      // Set data frame size to 8 bits
        .parity = UART_PARITY_DISABLE,      // Disable parity bit for simpler communication
        .stop_bits = UART_STOP_BITS_1,      // Use 1 stop bit to signal end of data frame
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,  // Disable hardware flow control (no RTS/CTS)
        .rx_flow_ctrl_thresh = 0            // Flow control threshold set to 0 (not used)
    };
   
    uart_param_config(UART_NUM, &uart_config);   // Apply the UART configuration to the specified UART port (UART_NUM_2) using pointer

    
    uart_set_pin(UART_NUM, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);   // Assign the UART TX and RX pins, leave RTS and CTS unassigned

   
    uart_driver_install(UART_NUM, 1024 * 2, 0, 0, NULL, 0);  // Install UART driver 
}


void sendData(const char* data) {   // Function to send data over UART
    
    uart_write_bytes(UART_NUM, data, strlen(data)); // Write the data to the UART port as a string
}