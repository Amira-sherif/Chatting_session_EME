#include "chat_app.h"
#include <stdio.h>

User_state state=ONLINE;

void chat_init(void)
{

    buttons_init();
    LEDs_init();
    UART0_init();
#ifdef UART7
    UART7_init();
#elif I2C

#endif

}

void chat_app(void)
{
    switch (state)
    {
    case OFFLINE:
        LEDs_allOff();
        LEDs_redOn();
     if (button==SW0)
        {
            state=READ_ONLY;
        }
        else if (button==SW4)
         {
           state=ONLINE;
         }
        else
        {}
         button = NA;
         CLEAR_send();
         CLEAR_recieved();
        break;

    case READ_ONLY:
        LEDs_allOff();
        LEDs_blueOn();
        recieve();
        if (button==SW0)
        {
            state=ONLINE;
        }
        else if (button==SW4)
         {
           state=OFFLINE;
         }
        else
        {

        }
        button = NA;
        break;
    case ONLINE:

        LEDs_allOff();
        LEDs_whiteOn();
        send();
        recieve();


        if (button==SW0)
        {
            state=OFFLINE;
        }
        else if (button==SW4)
         {
           state=READ_ONLY;
         }
        else
        {

        }
        button = NA;

        break;
    default:
        button = NA;
        CLEAR_recieved();
        CLEAR_send();
        break;
    }
}
