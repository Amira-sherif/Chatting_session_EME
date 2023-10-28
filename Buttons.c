#include "Buttons.h"

pressed_button button=NA;
void buttons_init()
{
    /*Enabling the clock for portF*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); /*Enable PortF peripheral , it takes 5 clk cycles to make the peripheral ready*/
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)) /*wait for the GPIOF module to be ready*/
     {}

    /*UNLOCK the pins*/
    GPIO_PORTF_LOCK_R =0x4c4f434b;
    GPIO_PORTF_CR_R  =0xff;
    GPIO_PORTF_PUR_R=0x11;

    /*set PF0 and PF4 as input*/
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0 );
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4 );

    /*setup buttons interrupts*/
    GPIOIntTypeSet(GPIO_PORTF_BASE,(GPIO_PIN_0 | GPIO_PIN_4), GPIO_FALLING_EDGE);
    GPIOPadConfigSet(GPIO_PORTF_BASE,(GPIO_PIN_0|GPIO_PIN_4),GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU); /*configure switches to have an internal pull-up resistors*/
    IntPrioritySet(INT_GPIOF, 2);
    GPIOIntRegister(GPIO_PORTF_BASE,portF_IntHandler);
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4 ); /*Enable the pin interrupts*/
    IntEnable(INT_GPIOF);
    IntMasterEnable();

}


/*Interrupts service routines*/

    void portF_IntHandler(void)
    {
        uint32_t status;
        /* Read and clear the interrupt status*/
        status = GPIOIntStatus(GPIO_PORTF_BASE, true);
        GPIOIntClear(GPIO_PORTF_BASE, status);

        /* Check if Switch 1 generated the interrupt*/
        if (status & GPIO_PIN_4)
        {
            button=SW4;

        }

        /* Check if Switch 0 generated the interrupt*/
        if (status & GPIO_PIN_0)
        {
            button=SW0;

        }
    }


