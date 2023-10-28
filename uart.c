
#include "UART.h"
#define GPIO_PORTF_DATA_R       (*((volatile uint32_t *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile uint32_t *)0x40025400))
#define GPIO_PORTF_PUR_R        (*((volatile uint32_t *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile uint32_t *)0x4002551C))


#define BACKSPACE (uint8_t)8
volatile uint8_t U0_receivedData[UART_BUFFER_SIZE];
volatile uint8_t U7_receivedData[UART_BUFFER_SIZE];
volatile uint32_t uartIndex = 0;
volatile uint32_t uart7_Index = 0;
volatile uint8_t uartDataReady = 0;
volatile uint8_t send_flag=0;
volatile uint8_t recieve_flag=0;
uint8_t* error_msg="\rMessage limit exceeded. The message has been ignored.\n";
uint8_t* USER_NAME="MARIAM:";

void UART0_IntHandler(void)
{
    send_flag=1;
    uint32_t status = UARTIntStatus(UART0_BASE, true);
    UARTIntClear(UART0_BASE, status);

}
void send(void)
{   if(send_flag)
      {
        uint8_t i=0;
        uartIndex=0;
        uint8_t temp_char,error_flag=0;

        while (UARTCharsAvail(UART0_BASE))
        {
            do
            {
                temp_char=UARTCharGet(UART0_BASE);
                if(temp_char==BACKSPACE){
                    uartIndex--;
                }
                else
                {
                U0_receivedData[uartIndex] = temp_char;

                uartIndex++;

                if(uartIndex==UART_BUFFER_SIZE)
                {
                    error_flag=1;
                    UART0_putString(error_msg);
                    UARTCharPut(UART0_BASE, '\r');
                    uartIndex = 0;
                    break;
                }
                }
            }
            while(temp_char!='\x0d');
        }
        if(!error_flag){



        for(i =0;i<uartIndex;i++)
        {
            UARTCharPut(UART7_BASE, U0_receivedData[i] );
        }
            UARTCharPut(UART0_BASE, '\n' );

        }
        else
        {
            uartIndex=0;
            error_flag=0;
        }
        send_flag=0;
    }
    }
void UART0_init(void)
{
       /* Enable UART0 and GPIO Port A*/
       SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
       SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

       /* Configure UART0 pins*/
       GPIOPinConfigure(GPIO_PA0_U0RX);
       GPIOPinConfigure(GPIO_PA1_U0TX);
       GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

       /* Configure UART0 with a baud rate of 9600*/
       UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 9600,
                          (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
       UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);
       /* Enable UART0 interrupt*/
       UARTIntRegister(UART0_BASE, UART0_IntHandler);
       UARTIntEnable(UART0_BASE, UART_INT_RX);

       IntPrioritySet(INT_UART0, 0);  // Set interrupt priority to 0 (highest)

       /* Enable UART0 interrupt in the NVIC*/
       IntEnable(INT_UART0);

       /* Enable global interrupts*/
       IntMasterEnable();
}

void UART0_putString(uint8_t *str)
{
    uint8_t i=0;
    while(UARTBusy(UART0_BASE)){}
    UARTCharPut(UART0_BASE, '\r');
    while(str[i]!='\0')
    {
        UARTCharPut(UART0_BASE, str[i]);
        i++;
    }
 }

#ifdef UART7
void UART7_IntHandler(void)
{
    recieve_flag=1;
    uint32_t status = UARTIntStatus(UART7_BASE, true);
    UARTIntClear(UART7_BASE, status);

}
void recieve(void)
{
    if(recieve_flag){
    uart7_Index=0;

    uint8_t temp_char;

    while (UARTCharsAvail(UART7_BASE))
    {

        do
        {
            temp_char=UARTCharGet(UART7_BASE);

            U7_receivedData[uart7_Index] = temp_char;

            UARTCharPut(UART0_BASE,U7_receivedData[uart7_Index] );
            uart7_Index++;
        }
        while(temp_char!='\x0d');
        UARTCharPut(UART0_BASE,'\n' );
    }
    }
    recieve_flag=0;
    }
void UART7_init(void)
{
       /* Enable UART0 and GPIO Port A*/
       SysCtlPeripheralEnable(SYSCTL_PERIPH_UART7);
       SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

       /* Configure UART0 pins*/
       GPIOPinConfigure(GPIO_PE0_U7RX);
       GPIOPinConfigure(GPIO_PE1_U7TX);
       GPIOPinTypeUART(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1);

       /* Configure UART0 with a baud rate of 9600*/
       UARTConfigSetExpClk(UART7_BASE, SysCtlClockGet(), 9600,
                          (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
       UARTFIFOLevelSet(UART7_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);
       /* Enable UART0 interrupt*/
       UARTIntRegister(UART7_BASE, UART7_IntHandler);
       UARTIntEnable(UART7_BASE, UART_INT_RX);

       IntPrioritySet(INT_UART7, 1);  // Set interrupt priority to 1 (highest)

       /* Enable UART0 interrupt in the NVIC*/
       IntEnable(INT_UART7);

       /* Enable global interrupts*/
       IntMasterEnable();
}
void CLEAR_recieved(void){
    recieve_flag=0;

}
void CLEAR_send(void){
    send_flag=0;

}
#endif

