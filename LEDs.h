

#ifndef LEDS_H_
#define LEDS_H_


#include <stdbool.h>
#include <stdint.h>
#include "driverlib/gpio.h"
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"


void LEDs_init(void);
void LEDs_blueOn(void);
void LEDs_redOn(void);
void LEDs_whiteOn(void);
void LEDs_allOff(void);


#endif /* LEDS_H_ */
