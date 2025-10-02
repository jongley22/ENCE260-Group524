#include "system.h"
#include "pio.h"
#include "pacer.h"
#include <stdbool.h>
#include "led_selector.h"


extern bool BO_LED1_1 = 0; //status of led 1_1
extern bool BO_LED7_1 = 0; //status of led 1_17
extern bool BO_ED1_5 = 0; //status of led 1_17


// system_init();

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






void LED_ACTIVATOR(uint8_t i,uint8_t j){
    for (uint8_t t = 0; t < 6; t++) {
        if (t == i) {          
            pio_output_low(rows[t]);
        }
        else  {           
            pio_output_high(rows[t]);
        }
    }
    for (uint8_t x = 0; x < 4; x++) {
        if (x == j){
            pio_output_low(cols[x]);
        }
        else {
            pio_output_high(cols[x]);
        }
    }
}


// void LED1_1(bool bol)
// {
//     if (bol) {
//         pio_output_low(LEDMAT_COL1_PIO);
//         pio_output_low(LEDMAT_ROW1_PIO);

//         pio_output_high(LEDMAT_COL2_PIO);
//         pio_output_high(LEDMAT_COL3_PIO);
//         pio_output_high(LEDMAT_COL4_PIO);
//         pio_output_high(LEDMAT_COL5_PIO);
//         pio_output_high(LEDMAT_ROW2_PIO);
//         pio_output_high(LEDMAT_ROW3_PIO);
//         pio_output_high(LEDMAT_ROW4_PIO);
//         pio_output_high(LEDMAT_ROW5_PIO);
//         pio_output_high(LEDMAT_ROW6_PIO);
//         pio_output_high(LEDMAT_ROW7_PIO);
//     } else {
//         pio_output_high(LEDMAT_COL1_PIO);
//         pio_output_high(LEDMAT_COL2_PIO);
//         pio_output_high(LEDMAT_COL3_PIO);
//         pio_output_high(LEDMAT_COL4_PIO);
//         pio_output_high(LEDMAT_COL5_PIO);
//         pio_output_high(LEDMAT_ROW1_PIO);
//         pio_output_high(LEDMAT_ROW2_PIO);
//         pio_output_high(LEDMAT_ROW3_PIO);
//         pio_output_high(LEDMAT_ROW4_PIO);
//         pio_output_high(LEDMAT_ROW5_PIO);
//         pio_output_high(LEDMAT_ROW6_PIO);
//         pio_output_high(LEDMAT_ROW7_PIO);
//     }
// }

// void LED1_5(bool bol)
// {
//     if (bol) {
//         pio_output_low(LEDMAT_COL5_PIO);
//         pio_output_low(LEDMAT_ROW1_PIO);

//         pio_output_high(LEDMAT_COL2_PIO);
//         pio_output_high(LEDMAT_COL3_PIO);
//         pio_output_high(LEDMAT_COL4_PIO);
//         pio_output_high(LEDMAT_COL1_PIO);
//         pio_output_high(LEDMAT_ROW2_PIO);
//         pio_output_high(LEDMAT_ROW3_PIO);
//         pio_output_high(LEDMAT_ROW4_PIO);
//         pio_output_high(LEDMAT_ROW5_PIO);
//         pio_output_high(LEDMAT_ROW6_PIO);
//         pio_output_high(LEDMAT_ROW7_PIO);
//     } else {
//         pio_output_high(LEDMAT_COL1_PIO);
//         pio_output_high(LEDMAT_COL2_PIO);
//         pio_output_high(LEDMAT_COL3_PIO);
//         pio_output_high(LEDMAT_COL4_PIO);
//         pio_output_high(LEDMAT_COL5_PIO);
//         pio_output_high(LEDMAT_ROW1_PIO);
//         pio_output_high(LEDMAT_ROW2_PIO);
//         pio_output_high(LEDMAT_ROW3_PIO);
//         pio_output_high(LEDMAT_ROW4_PIO);
//         pio_output_high(LEDMAT_ROW5_PIO);
//         pio_output_high(LEDMAT_ROW6_PIO);
//         pio_output_high(LEDMAT_ROW7_PIO);
//     }
// }

// void LED1_7(bool bol)
// {
//     if (bol) {
//         pio_output_low(LEDMAT_COL1_PIO);
//         pio_output_low(LEDMAT_ROW7_PIO);

//         pio_output_high(LEDMAT_COL2_PIO);
//         pio_output_high(LEDMAT_COL3_PIO);
//         pio_output_high(LEDMAT_COL4_PIO);
//         pio_output_high(LEDMAT_COL5_PIO);
//         pio_output_high(LEDMAT_ROW2_PIO);
//         pio_output_high(LEDMAT_ROW3_PIO);
//         pio_output_high(LEDMAT_ROW4_PIO);
//         pio_output_high(LEDMAT_ROW5_PIO);
//         pio_output_high(LEDMAT_ROW6_PIO);
//         pio_output_high(LEDMAT_ROW1_PIO);
//     } else {
//         pio_output_high(LEDMAT_COL1_PIO);
//         pio_output_high(LEDMAT_COL2_PIO);
//         pio_output_high(LEDMAT_COL3_PIO);
//         pio_output_high(LEDMAT_COL4_PIO);
//         pio_output_high(LEDMAT_COL5_PIO);
//         pio_output_high(LEDMAT_ROW1_PIO);
//         pio_output_high(LEDMAT_ROW2_PIO);
//         pio_output_high(LEDMAT_ROW3_PIO);
//         pio_output_high(LEDMAT_ROW4_PIO);
//         pio_output_high(LEDMAT_ROW5_PIO);
//         pio_output_high(LEDMAT_ROW6_PIO);
//         pio_output_high(LEDMAT_ROW7_PIO);
//     }
// }