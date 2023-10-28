

#ifndef CHAT_APP_H_
#define CHAT_APP_H_

#include "UART.h"
#include "Buttons.h"
#include "LEDs.h"

typedef enum{OFFLINE,READ_ONLY,ONLINE} User_state;


void chat_init(void);
void chat_app(void);


#endif /* CHAT_APP_H_ */
