
#ifndef UART_H_
#define UART_H_
#include <stdbool.h>
#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "driverlib/interrupt.h"

#define UART_BUFFER_SIZE 200
#define UART7

extern volatile uint8_t U0_receivedData[UART_BUFFER_SIZE];
extern volatile uint32_t uartIndex;
extern volatile uint8_t uartDataReady ;


void UART0_init(void);
void UART0_IntHandler(void);
void UART0_putString(uint8_t *str);
void UART7_init(void);
void UART7_IntHandler(void);
void recieve(void);
void send(void);
void CLEAR_recieved(void);
void CLEAR_send(void);



#endif /* UART_H_ */
