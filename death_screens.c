#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "led_selector.h"
#include "apples.h"
#include "movement_his.h"


static uint8_t current_column = 0; 
/** Define PIO pins driving LED matrix d_rows.  */
static const pio_t d_d_rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO, 
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};


/** Define PIO pins driving LED matrix columns.  */
static const pio_t d_cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};


// static const uint8_t death_display_bitmap[] =
// {
//     0x30, 0x46, 0x40, 0x46, 0x30
// };

static uint8_t death_display_bitmap[] =
{
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000
};


static uint8_t L_bm[] = 
{
    0b00001000,
    0b00001000,
    0b00001000,
    0b00001000,
    0b00001111 
};


void death_display_column (uint8_t row_pattern, uint8_t current_column)
{
    /* TODO */

    static uint8_t prev_col =0; //statics after they have been declared will ignore there declaration afterwards so it will only see prev_col = current_column;
    pio_output_high(d_cols[prev_col]); //we need to turn previos col off

    for (uint8_t i = 0; i < 7; i++) {
        uint8_t current_row = i;
    if ((row_pattern >> current_row) & 1) { // if row pattern 0110 0000  then 0110 0000 >> 2 = 0001 1000 shifting by relavent row index to check its right most value is 1 or 0
        pio_output_low(d_rows[current_row]);
    }
    else {
        pio_output_high(d_rows[current_row]);

    }


}   
    pio_output_low(cols[current_column]);
    d_prev_col = current_column; 
}

void death_led_while(void) 
{
    pacer_wait ();
    
    death_display_column(death_display_bitmap[current_column], current_column);


    current_column++;

    if (current_column > (LEDMAT_COLS_NUM - 1))
    {
        current_column = 0;
    }  
}

void death_screen(void) {

    for (uint8_t j_search = 0; j_search < 5; j_search++) {
        death_display_bitmap[j_search] = L_bm[j_search];
    }
}