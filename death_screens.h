#ifndef DEATH_DISPLAY_H
#define DEATH_DISPLAY_H

#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "led_selector.h"
#include "apples.h"
#include "movement_his.h"

/** Display a single column of the death screen LED pattern. */
void death_display_column(uint8_t row_pattern, uint8_t current_column);

/** Update the LED matrix with the current death display pattern. */
void death_led_while(void);

/** Set up the death screen bitmap (e.g., show 'L' or similar). */
void death_screen(void);

#endif // DEATH_DISPLAY_H
