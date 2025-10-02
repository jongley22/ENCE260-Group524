// #include "system.h"
// #include "pio.h"
// #include "pacer.h"
// #include <stdbool.h>
// #include "led_selector.h"


// extern bool BO_LED1_1 = 0; //status of led 1_1
// extern bool BO_LED7_1 = 0; //status of led 1_17
// extern bool BO_ED1_5 = 0; //status of led 1_17


// // system_init();

// static const pio_t rows[] =
// {
//     LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO, 
//     LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
//     LEDMAT_ROW7_PIO
// };


// /** Define PIO pins driving LED matrix columns.  */
// static const pio_t cols[] =
// {
//     LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
//     LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
// };






// void LED_ACTIVATOR(uint8_t i,uint8_t j){
//     for (uint8_t t = 0; t < 6; t++) {
//         if (t == i) {          
//             pio_output_low(rows[t]);
//         }
//         else  {           
//             pio_output_high(rows[t]);
//         }
//     }
//     for (uint8_t x = 0; x < 4; x++) {
//         if (x == j){
//             pio_output_low(cols[x]);
//         }
//         else {
//             pio_output_high(cols[x]);
//         }
//     }
// }


// // void LED1_1(bool bol)
// // {
// //     if (bol) {
// //         pio_output_low(LEDMAT_COL1_PIO);
// //         pio_output_low(LEDMAT_ROW1_PIO);

// //         pio_output_high(LEDMAT_COL2_PIO);
// //         pio_output_high(LEDMAT_COL3_PIO);
// //         pio_output_high(LEDMAT_COL4_PIO);
// //         pio_output_high(LEDMAT_COL5_PIO);
// //         pio_output_high(LEDMAT_ROW2_PIO);
// //         pio_output_high(LEDMAT_ROW3_PIO);
// //         pio_output_high(LEDMAT_ROW4_PIO);
// //         pio_output_high(LEDMAT_ROW5_PIO);
// //         pio_output_high(LEDMAT_ROW6_PIO);
// //         pio_output_high(LEDMAT_ROW7_PIO);
// //     } else {
// //         pio_output_high(LEDMAT_COL1_PIO);
// //         pio_output_high(LEDMAT_COL2_PIO);
// //         pio_output_high(LEDMAT_COL3_PIO);
// //         pio_output_high(LEDMAT_COL4_PIO);
// //         pio_output_high(LEDMAT_COL5_PIO);
// //         pio_output_high(LEDMAT_ROW1_PIO);
// //         pio_output_high(LEDMAT_ROW2_PIO);
// //         pio_output_high(LEDMAT_ROW3_PIO);
// //         pio_output_high(LEDMAT_ROW4_PIO);
// //         pio_output_high(LEDMAT_ROW5_PIO);
// //         pio_output_high(LEDMAT_ROW6_PIO);
// //         pio_output_high(LEDMAT_ROW7_PIO);
// //     }
// // }

// // void LED1_5(bool bol)
// // {
// //     if (bol) {
// //         pio_output_low(LEDMAT_COL5_PIO);
// //         pio_output_low(LEDMAT_ROW1_PIO);

// //         pio_output_high(LEDMAT_COL2_PIO);
// //         pio_output_high(LEDMAT_COL3_PIO);
// //         pio_output_high(LEDMAT_COL4_PIO);
// //         pio_output_high(LEDMAT_COL1_PIO);
// //         pio_output_high(LEDMAT_ROW2_PIO);
// //         pio_output_high(LEDMAT_ROW3_PIO);
// //         pio_output_high(LEDMAT_ROW4_PIO);
// //         pio_output_high(LEDMAT_ROW5_PIO);
// //         pio_output_high(LEDMAT_ROW6_PIO);
// //         pio_output_high(LEDMAT_ROW7_PIO);
// //     } else {
// //         pio_output_high(LEDMAT_COL1_PIO);
// //         pio_output_high(LEDMAT_COL2_PIO);
// //         pio_output_high(LEDMAT_COL3_PIO);
// //         pio_output_high(LEDMAT_COL4_PIO);
// //         pio_output_high(LEDMAT_COL5_PIO);
// //         pio_output_high(LEDMAT_ROW1_PIO);
// //         pio_output_high(LEDMAT_ROW2_PIO);
// //         pio_output_high(LEDMAT_ROW3_PIO);
// //         pio_output_high(LEDMAT_ROW4_PIO);
// //         pio_output_high(LEDMAT_ROW5_PIO);
// //         pio_output_high(LEDMAT_ROW6_PIO);
// //         pio_output_high(LEDMAT_ROW7_PIO);
// //     }
// // }

// // void LED1_7(bool bol)
// // {
// //     if (bol) {
// //         pio_output_low(LEDMAT_COL1_PIO);
// //         pio_output_low(LEDMAT_ROW7_PIO);

// //         pio_output_high(LEDMAT_COL2_PIO);
// //         pio_output_high(LEDMAT_COL3_PIO);
// //         pio_output_high(LEDMAT_COL4_PIO);
// //         pio_output_high(LEDMAT_COL5_PIO);
// //         pio_output_high(LEDMAT_ROW2_PIO);
// //         pio_output_high(LEDMAT_ROW3_PIO);
// //         pio_output_high(LEDMAT_ROW4_PIO);
// //         pio_output_high(LEDMAT_ROW5_PIO);
// //         pio_output_high(LEDMAT_ROW6_PIO);
// //         pio_output_high(LEDMAT_ROW1_PIO);
// //     } else {
// //         pio_output_high(LEDMAT_COL1_PIO);
// //         pio_output_high(LEDMAT_COL2_PIO);
// //         pio_output_high(LEDMAT_COL3_PIO);
// //         pio_output_high(LEDMAT_COL4_PIO);
// //         pio_output_high(LEDMAT_COL5_PIO);
// //         pio_output_high(LEDMAT_ROW1_PIO);
// //         pio_output_high(LEDMAT_ROW2_PIO);
// //         pio_output_high(LEDMAT_ROW3_PIO);
// //         pio_output_high(LEDMAT_ROW4_PIO);
// //         pio_output_high(LEDMAT_ROW5_PIO);
// //         pio_output_high(LEDMAT_ROW6_PIO);
// //         pio_output_high(LEDMAT_ROW7_PIO);
// //     }
// // }

#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "led_selector.h"

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


// static const uint8_t bitmap[] =
// {
//     0x30, 0x46, 0x40, 0x46, 0x30
// };

static const uint8_t bitmap[] =
{
    0b00110001,
    0b01000110,
    0b01000000,
    0b01000110,
    0b00110000
};


static void display_column (uint8_t row_pattern, uint8_t current_column)
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
    prev_col = current_column; //
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
    
    display_column(bitmap[current_column], current_column);


    current_column++;

    if (current_column > (LEDMAT_COLS_NUM - 1))
    {
        current_column = 0;
    }  
}
