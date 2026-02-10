#include "main.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

UART_HandleTypeDef huart1;

int _write(int file, char *ptr, int len) {
    HAL_UART_Transmit(&huart1, (uint8_t *)ptr, len, HAL_MAX_DELAY);
    return len;
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();

    printf("\r\n=== STM32N6570-DK UART VCP Test ===\r\n");
    printf("USART1 PE5(TX)/PE6(RX) -> STLINK VCOM\r\n");
    printf("Baud: 115200 8-E-1-N\r\n\r\n");

    uint32_t counter = 0;
    uint8_t rx_char;
    
    while (1)
    {
        printf("[T+%lu] Hello VCP! Counter: %lu\r\n", HAL_GetTick()/1000, counter++);
        
        if(HAL_UART_Receive(&huart1, &rx_char, 1, 10) == HAL_OK) {
            printf("\r\nRX <- '%c' (0x%02X)\r\n> ", rx_char, rx_char);
            HAL_UART_Transmit(&huart1, &rx_char, 1, HAL_MAX_DELAY);
        }
        
        HAL_Delay(1000);
    }
}

void SystemClock_Config(void) { }
void MX_GPIO_Init(void) { }
void MX_USART1_UART_Init(void) { }
