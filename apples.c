/*------------------------------------------------------------
 * File:        apples.c
 * Authors:     Maxwell Beran & Josh Ongley
 * Description: Handles random apple generation and display 
 *              on the LED matrix for the Slither game.
 *------------------------------------------------------------*/

#include "navswitch.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "apples.h"
#include "led_selector.h"

static uint8_t apple_counter = 1;

/* Generates a random coordinate for the apple and displays it */
void coord_generator(void)
{
    navswitch_update();

    int app_i = rand() % 7;
    int app_j = rand() % 4;

    display_apple(app_i, app_j);
}

/* Displays an apple at the given coordinates */
void display_apple(uint8_t i_display, uint8_t j_display)
{
    apples_bm_sel(i_display, j_display, 1);
    apples_bm_sel(0, 0, 0);   // Fixes (0,0) LED being on at init
    apple_counter++;
}

