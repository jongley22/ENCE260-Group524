#ifndef LEDMAT_H
#define LEDMAT_H

#include "system.h"
#include "pio.h"
#include "pacer.h"


/** Define PIO pins driving LED matrix rows. */
static const pio_t rows[7];

/** Define PIO pins driving LED matrix columns. */
static const pio_t cols[5];

/** Bitmap for LED matrix display. */

/** Function to display a column on the LED matrix.
 * @param row_pattern The pattern to display on the rows.
 * @param current_column The column to activate.
 */
void display_column(uint8_t row_pattern, uint8_t current_column);

void led_while(void);

void led_init(void);

void led_selector(uint8_t i, uint8_t j, uint8_t bol);

void bitmap_complier(void);

void snake_head_bm_sel(uint8_t i, uint8_t j, uint8_t bol);

//apple code 

void display_apple(uint8_t i_display,uint8_t j_display);

void coord_generator(void);

#endif /* LEDMAT_H */