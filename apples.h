/*------------------------------------------------------------
 * File:        apples.h
 * Authors:     Maxwell Beran & Josh Ongley
 * Description: Header file for apple generation and display 
 *              functions used in the Slither game.
 *------------------------------------------------------------*/

#ifndef APPLE_LOGIC_H
#define APPLE_LOGIC_H

#include "navswitch.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "led_selector.h"

/* Generates a random apple coordinate and displays it */
void coord_generator(void);

/* Displays an apple at the specified LED matrix coordinates */
void display_apple(uint8_t i_display, uint8_t j_display);

#endif 
