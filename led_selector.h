// #ifndef LED_SELECTOR_H
// #define LED_SELECTOR_H
// #include "system.h"
// #include "pio.h"
// #include "pacer.h"
// #include <stdbool.h>

// extern bool BO_LED1_1;
// extern bool BO_LED7_1;
// extern bool BO_ED1_5;




// void LED_ACTIVATOR(uint8_t i,uint8_t j);
// void LED1_1(bool bol);

// #endif

// #ifndef BINARY_LED_SELECTOR
// #define BINARY_LED_SELECTOR
// #include "system.h"
// #include "pio.h"
// #include "pacer.h"

// /** Define PIO pins driving LED matrix rows.  */
// static const pio_t rows[];


// /** Define PIO pins driving LED matrix columns.  */
// static const pio_t cols[];

// // static const uint8_t bitmap[] =
// // {
// //     0x30, 0x46, 0x40, 0x46, 0x30
// // };

// static const uint8_t bitmap[];

// static void display_column (uint8_t row_pattern, uint8_t current_column);

// #endif
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
static uint8_t bitmap[5];

/** Function to display a column on the LED matrix.
 * @param row_pattern The pattern to display on the rows.
 * @param current_column The column to activate.
 */
static void display_column(uint8_t row_pattern, uint8_t current_column);

void led_while(void);

void led_selector(uint8_t i, uint8_t j, uint8_t bol);

#endif /* LEDMAT_H */