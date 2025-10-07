
#ifndef APPLE_LOGIC_H
#define APPLE_LOGIC_H

#include "navswitch.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "led_selector.h"

// Function declarations
void coord_generator(void);
void display_apple(uint8_t i_display, uint8_t j_display);
void apple_flasher(void);
#endif // APPLE_LOGIC_H