
#include "UART.h"
#include "driverlib/i2c.h"



// I2C slave address
#define I2C_SLAVE_ADDR 0x50

// Data buffer size
#define BUFFER_SIZE 8

// Data buffer
uint8_t dataBuffer[BUFFER_SIZE] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
#define max_recieved_size 50
uint8_t size=6;

uint8_t received_data[max_recieved_size];
void I2C_Master_init(void)
{
    /* Enable the I2C0 peripheral*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    /* Wait for the I2C0 module to be ready.
     */
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C0))
    {
    }
    /*Configure GPIO PINS for the data and clk signals*/
    GPIOPinConfigure(GPIO_PB2_I2C0SCL);
    GPIOPinConfigure(GPIO_PB3_I2C0SDA);
    GPIOPinTypeI2C(GPIO_PORTB_BASE,GPIO_PIN_3);
    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);

    I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);
    I2CMasterEnable(I2C0_BASE);


}

void I2C_slave_init(void)
{

    /* Enable the I2C0 peripheral*/
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    /* Wait for the I2C0 module to be ready.
     */
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C0))
    {
    }
    /*Configure GPIO PINS for the data and clk signals*/
    GPIOPinConfigure(GPIO_PB2_I2C0SCL);
    GPIOPinConfigure(GPIO_PB3_I2C0SDA);
    GPIOPinTypeI2C(GPIO_PORTB_BASE,GPIO_PIN_3);
    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
    I2CSlaveInit(I2C0_BASE, I2C_SLAVE_ADDR); // Set the slave address
    I2CSlaveEnable(I2C0_BASE);
    }
void I2C0_SendData(void)
{
    uint8_t i=0;

    char* str="hello";
    // Specify the slave address
    I2CMasterSlaveAddrSet(I2C0_BASE, I2C_SLAVE_ADDR, false);

    // Send data to the slave
    while(str[i]!='\0')
    {
        I2CMasterDataPut(I2C0_BASE, str[i]);
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);
        if(i==(size-1))
        {
            I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);
        }
        else {
            I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
        }
        i++;
    }



    // Wait until the busy bit is cleared
    while (I2CMasterBusy(I2C0_BASE))
    {
    }
}

void I2C0_read(void)
{
uint8_t i=0;
    I2CMasterSlaveAddrSet(I2C0_BASE, I2C_SLAVE_ADDR, true);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);
    while (I2CMasterBusy(I2C0_BASE))
     {
     }
    for (i=0;i<size;i++)
    {
        if(i==(size-1))
              {
                  I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_FIFO_BURST_RECEIVE_FINISH);
              }
              else {
                  I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
              }
        while (I2CMasterBusy(I2C0_BASE))
            {
            }
        received_data[i]=I2CMasterDataGet(I2C0_BASE);
    }


 }

void main(void)
  {
    I2C_slave_init();
    I2C0_read();

    while(1){}

    }










