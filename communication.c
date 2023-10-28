
void comm_init(void)
{
    UART0_init();
 #ifdef UART7
     UART7_init();
 #elif I2C

 #endif

}






