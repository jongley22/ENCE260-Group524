#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "led_selector.h"
#include "apples.h"
#include "movement_his.h"

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

static uint8_t snake_body_bm[] =
{
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000
};

static uint8_t opp_snake_head_bm[] =
{
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000
};

static uint8_t opp_snake_body_bm[] =
{
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000
};

static uint8_t apples_display_bm[] =
{
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000 
};

static uint8_t apples_on_bm[] =
{
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000 
};

static uint8_t blank_bm[] =
{
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000 
};

static uint8_t led_bm[] = 
{
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000 
};

static uint8_t hiden_zone_bm[] = 
{
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b01111111 
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

void led_init_custom(void) 
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
            led_bm[j] |= (1 << i); // Set bit i in display_bitmap[j] to 1
        } else {
            led_bm[j] &= ~(1 << i); // Clear bit i in display_bitmap[j] to 0
        }
    }
}

void snake_head_bm_sel(uint8_t i, uint8_t j, uint8_t bol)
{
    if (i < 7 && j < 5) { // Valvoid snake_head_bm_sel(uint8_t i, uint8_t j, uint8_t bol)
{
    if (i < 7 && j < 5) { // Validate indices
        if (bol) {
            snake_head_bm[j] |= (1 << i); // Set bit i in display_bitmap[j] to 1
        } else {
            snake_head_bm[j] &= ~(1 << i); // Clear bit i in display_bitmap[j] to 0
        }
    }
}
        if (bol) {
            snake_head_bm[j] |= (1 << i); // Set bit i in display_bitmap[j] to 1
        } else {
            snake_head_bm[j] &= ~(1 << i); // Clear bit i in display_bitmap[j] to 0
        }
    }
}

void snake_body_bm_sel(uint8_t i, uint8_t j, uint8_t bol)
{
    if (i < 7 && j < 5) { // Validate indices
        if (bol) {
            snake_body_bm[j] |= (1 << i); // Set bit i in display_bitmap[j] to 1
        } else {
            snake_body_bm[j] &= ~(1 << i); // Clear bit i in display_bitmap[j] to 0
        }
    }
}

void op_snake_body_bm_sel(uint8_t i, uint8_t j, uint8_t bol)
{
    if (i < 7 && j < 5) { // Validate indices
        if (bol) {
            opp_snake_body_bm[j] |= (1 << i); // Set bit i in display_bitmap[j] to 1
        } else {
            opp_snake_body_bm[j] &= ~(1 << i); // Clear bit i in display_bitmap[j] to 0
        }
    }
}

void op_snake_head_bm_sel(uint8_t i, uint8_t j, uint8_t bol)
{
    if (i < 7 && j < 5) { // Validate indices
        if (bol) {
            opp_snake_head_bm[j] |= (1 << i); // Set bit i in display_bitmap[j] to 1
        } else {
            opp_snake_head_bm[j] &= ~(1 << i); // Clear bit i in display_bitmap[j] to 0
        }
    }
}


void apples_bm_sel(uint8_t i, uint8_t j, uint8_t bol)
{
    if (i < 7 && j < 5) { // Validate indices
        if (bol) {
            apples_on_bm[j] |= (1 << i); // Set bit i in display_bitmap[j] to 1
        } else {
            apples_on_bm[j] &= ~(1 << i); // Clear bit i in display_bitmap[j] to 0
        }
    }
}


bool apple_eaten(Pair *out_pair) {
    for (int j = 0; j < 5; j++) {           // each row
        uint8_t overlap = snake_head_bm[j] & apples_on_bm[j];
        if (overlap != 0) {                 // found at least one overlap in this row
            for (int i = 0; i < 8; i++) {   // check each bit in the row
                if (overlap & (1 << i)) {
                    out_pair->i = i;
                    out_pair->j = j;
                    return true;
                }
            }
        }
    }
    return false; // no overlap
}


void bitmap_complier(void)
{
    for (uint8_t j_search = 0; j_search < 5; j_search++) {
        display_bitmap[j_search] = snake_body_bm[j_search] | snake_head_bm[j_search] | apples_on_bm[j_search] 
                                | opp_snake_body_bm[j_search] | opp_snake_head_bm[j_search] | hiden_zone_bm[j_search]; // snake_head_bm[j_search] || 
    }
}
