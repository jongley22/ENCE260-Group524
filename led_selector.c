#include "system.h"
#include "pio.h"
#include "pacer.h"
#include <stdbool.h>
#include "led_selector.h"

extern bool BO_LED1_1 = 0; //status of led 1_1
extern bool BO_LED7_1 = 0; //status of led 1_17
extern bool BO_ED1_5 = 0; //status of led 1_17


// system_init();

// pio_config_set(LEDMAT_ROW1_PIO, PIO_OUTPUT_HIGH);
// pio_config_set(LEDMAT_ROW2_PIO, PIO_OUTPUT_HIGH);
// pio_config_set(LEDMAT_ROW3_PIO, PIO_OUTPUT_HIGH);
// pio_config_set(LEDMAT_ROW4_PIO, PIO_OUTPUT_HIGH);
// pio_config_set(LEDMAT_ROW5_PIO, PIO_OUTPUT_HIGH);
// pio_config_set(LEDMAT_ROW6_PIO, PIO_OUTPUT_HIGH);
// pio_config_set(LEDMAT_ROW7_PIO, PIO_OUTPUT_HIGH);

// pio_config_set(LEDMAT_COL1_PIO, PIO_OUTPUT_HIGH);
// pio_config_set(LEDMAT_COL2_PIO, PIO_OUTPUT_HIGH);
// pio_config_set(LEDMAT_COL3_PIO, PIO_OUTPUT_HIGH);
// pio_config_set(LEDMAT_COL4_PIO, PIO_OUTPUT_HIGH);
// pio_config_set(LEDMAT_COL5_PIO, PIO_OUTPUT_HIGH);

void LED1_1(bool bol)
{
    if (bol) {
        pio_output_low(LEDMAT_COL1_PIO);
        pio_output_low(LEDMAT_ROW1_PIO);

        pio_output_high(LEDMAT_COL2_PIO);
        pio_output_high(LEDMAT_COL3_PIO);
        pio_output_high(LEDMAT_COL4_PIO);
        pio_output_high(LEDMAT_COL5_PIO);
        pio_output_high(LEDMAT_ROW2_PIO);
        pio_output_high(LEDMAT_ROW3_PIO);
        pio_output_high(LEDMAT_ROW4_PIO);
        pio_output_high(LEDMAT_ROW5_PIO);
        pio_output_high(LEDMAT_ROW6_PIO);
        pio_output_high(LEDMAT_ROW7_PIO);
    } else {
        pio_output_high(LEDMAT_COL1_PIO);
        pio_output_high(LEDMAT_COL2_PIO);
        pio_output_high(LEDMAT_COL3_PIO);
        pio_output_high(LEDMAT_COL4_PIO);
        pio_output_high(LEDMAT_COL5_PIO);
        pio_output_high(LEDMAT_ROW1_PIO);
        pio_output_high(LEDMAT_ROW2_PIO);
        pio_output_high(LEDMAT_ROW3_PIO);
        pio_output_high(LEDMAT_ROW4_PIO);
        pio_output_high(LEDMAT_ROW5_PIO);
        pio_output_high(LEDMAT_ROW6_PIO);
        pio_output_high(LEDMAT_ROW7_PIO);
    }
}

void LED1_5(bool bol)
{
    if (bol) {
        pio_output_low(LEDMAT_COL5_PIO);
        pio_output_low(LEDMAT_ROW1_PIO);

        pio_output_high(LEDMAT_COL2_PIO);
        pio_output_high(LEDMAT_COL3_PIO);
        pio_output_high(LEDMAT_COL4_PIO);
        pio_output_high(LEDMAT_COL1_PIO);
        pio_output_high(LEDMAT_ROW2_PIO);
        pio_output_high(LEDMAT_ROW3_PIO);
        pio_output_high(LEDMAT_ROW4_PIO);
        pio_output_high(LEDMAT_ROW5_PIO);
        pio_output_high(LEDMAT_ROW6_PIO);
        pio_output_high(LEDMAT_ROW7_PIO);
    } else {
        pio_output_high(LEDMAT_COL1_PIO);
        pio_output_high(LEDMAT_COL2_PIO);
        pio_output_high(LEDMAT_COL3_PIO);
        pio_output_high(LEDMAT_COL4_PIO);
        pio_output_high(LEDMAT_COL5_PIO);
        pio_output_high(LEDMAT_ROW1_PIO);
        pio_output_high(LEDMAT_ROW2_PIO);
        pio_output_high(LEDMAT_ROW3_PIO);
        pio_output_high(LEDMAT_ROW4_PIO);
        pio_output_high(LEDMAT_ROW5_PIO);
        pio_output_high(LEDMAT_ROW6_PIO);
        pio_output_high(LEDMAT_ROW7_PIO);
    }
}

void LED1_7(bool bol)
{
    if (bol) {
        pio_output_low(LEDMAT_COL1_PIO);
        pio_output_low(LEDMAT_ROW7_PIO);

        pio_output_high(LEDMAT_COL2_PIO);
        pio_output_high(LEDMAT_COL3_PIO);
        pio_output_high(LEDMAT_COL4_PIO);
        pio_output_high(LEDMAT_COL5_PIO);
        pio_output_high(LEDMAT_ROW2_PIO);
        pio_output_high(LEDMAT_ROW3_PIO);
        pio_output_high(LEDMAT_ROW4_PIO);
        pio_output_high(LEDMAT_ROW5_PIO);
        pio_output_high(LEDMAT_ROW6_PIO);
        pio_output_high(LEDMAT_ROW1_PIO);
    } else {
        pio_output_high(LEDMAT_COL1_PIO);
        pio_output_high(LEDMAT_COL2_PIO);
        pio_output_high(LEDMAT_COL3_PIO);
        pio_output_high(LEDMAT_COL4_PIO);
        pio_output_high(LEDMAT_COL5_PIO);
        pio_output_high(LEDMAT_ROW1_PIO);
        pio_output_high(LEDMAT_ROW2_PIO);
        pio_output_high(LEDMAT_ROW3_PIO);
        pio_output_high(LEDMAT_ROW4_PIO);
        pio_output_high(LEDMAT_ROW5_PIO);
        pio_output_high(LEDMAT_ROW6_PIO);
        pio_output_high(LEDMAT_ROW7_PIO);
    }
}