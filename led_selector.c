#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "led_selector.h"
// Header files for apple spawner
#include "navswitch.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
static uint8_t current_column = 0; 
/** Define PIO pins driving LED matrix rows.  */
static const pio_t rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO, 
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};


/** Define PIO pins driving LED matrix columns.  */
static const pio_t cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};


// static const uint8_t display_bitmap[] =
// {
//     0x30, 0x46, 0x40, 0x46, 0x30
// };

static uint8_t display_bitmap[] =
{
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000
};

static uint8_t snake_head_bm[] =
{
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000
};



void display_column (uint8_t row_pattern, uint8_t current_column)
{
    /* TODO */

    static uint8_t prev_col =0; //statics after they have been declared will ignore there declaration afterwards so it will only see prev_col = current_column;
    pio_output_high(cols[prev_col]); //we need to turn previos col off

    for (uint8_t i = 0; i < 7; i++) {
        uint8_t current_row = i;
    if ((row_pattern >> current_row) & 1) { // if row pattern 0110 0000  then 0110 0000 >> 2 = 0001 1000 shifting by relavent row index to check its right most value is 1 or 0
        pio_output_low(rows[current_row]);
    }
    else {
        pio_output_high(rows[current_row]);

    }


}   
    pio_output_low(cols[current_column]);
    prev_col = current_column; 
}

void led_init(void) 
{

  
    system_init ();
    pacer_init (500);
    
    /* TODO: Initialise LED matrix pins.  */
    for (uint8_t i = 0; i < 7; i++) {
        pio_config_set(rows[i], PIO_OUTPUT_HIGH);
    }
    for (uint8_t i = 0; i < 5; i++) {
        pio_config_set(cols[i], PIO_OUTPUT_HIGH);
    }
}
        

void led_while(void) 
{
    pacer_wait ();
    
    display_column(display_bitmap[current_column], current_column);


    current_column++;

    if (current_column > (LEDMAT_COLS_NUM - 1))
    {
        current_column = 0;
    }  
}

void led_selector(uint8_t i, uint8_t j, uint8_t bol)
{
    if (i < 7 && j < 5) { // Validate indices
        if (bol) {
            display_bitmap[j] |= (1 << i); // Set bit i in display_bitmap[j] to 1
        } else {
            display_bitmap[j] &= ~(1 << i); // Clear bit i in display_bitmap[j] to 0
        }
    }
}

// This is where Apple spawner Begins 

static uint8_t apple_counter = 1;

void coord_generator(void) {
    navswitch_update ();

    
    
    
    int app_i = rand() % 7;  
    int app_j = rand() % 5;  
    //int app_i = 1;  
    //int app_j = 1;  
    
    display_apple(app_i,app_j);
    
    
}
void display_apple(uint8_t i_display,uint8_t j_display){
    // pacer_init (100);
    // led_selector(i_display,j_display,1);
    // pacer_wait();
    // led_selector(i_display,j_display,0);
    // pacer_wait();
    led_selector(i_display,j_display,1);
    apple_counter++;

}

