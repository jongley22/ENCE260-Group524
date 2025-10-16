#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "led_selector.h"
#include "apples.h"
#include "movement_his.h"
#include "communication.h"

#define PACER_RATE 500 

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

static uint8_t L_bm[] = 
{
    0b00010000,
    0b00010000,
    0b00010000,
    0b00010000,
    0b0011100 
};
static uint8_t W_bm[] = 
{
    0b01000001,  
    0b01000001,  
    0b01001001, 
    0b01010101,  
    0b00100010   
};
static uint8_t T_bm[] = 
{
    0b01111110,
    0b00010000,
    0b00010000,
    0b00010000,
    0b00010000 
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


bool user_apple_eaten(Pair *out_pair) {
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

void apple_flasher(void) {
    uint64_t apple_rate = 10;
    uint64_t max_tick = PACER_RATE / apple_rate;
    static uint64_t ticker = 0;

    if (ticker <= max_tick/2) {
        for (uint8_t j_search = 0; j_search < 5; j_search++) {
            apples_display_bm[j_search] = apples_on_bm[j_search];
        }   
    }
    else if (ticker < max_tick) {   
        for (uint8_t j_search = 0; j_search < 5; j_search++) {
            apples_display_bm[j_search] = blank_bm[j_search];

        }
    }
    else {
        ticker = 0;
    }
    ticker++;
}


bool opp_apple_eaten(Pair *out_pair) {
    for (int j = 0; j < 5; j++) {           // each row
        uint8_t overlap = opp_snake_head_bm[j] & apples_on_bm[j];
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
        display_bitmap[j_search] = snake_body_bm[j_search] | snake_head_bm[j_search] | apples_display_bm[j_search] 
                                | opp_snake_body_bm[j_search] | opp_snake_head_bm[j_search] | hiden_zone_bm[j_search]; 
    }
}

void death_screen(void) {

    for (uint8_t j_search = 0; j_search < 5; j_search++) {
        display_bitmap[j_search] = blank_bm[j_search];
    }
}

void L_death_screen(void) {

    for (uint8_t j_search = 0; j_search < 5; j_search++) {
        display_bitmap[j_search] = L_bm[j_search];
    }
}
void W_death_screen(void) {

    for (uint8_t j_search = 0; j_search < 5; j_search++) {
        display_bitmap[j_search] = W_bm[j_search];
    }
}
void T_death_screen(void) {

    for (uint8_t j_search = 0; j_search < 5; j_search++) {
        display_bitmap[j_search] = T_bm[j_search];
    }
}
// snake_head_bm[j_search] || 
void game_finnished(Coords cord_status)
{
    int i = cord_status.i;
    int j = cord_status.j;
    int i_opp = cord_status.i_opp;
    int j_opp = cord_status.j_opp;

    bool hit = false;

    // reset flags for this tick
    user_head_opp_body_overlap      = false;
    opp_head_user_body_overlap      = false;
    head_to_head_overlap            = false;
    head_to_body_overlap            = false;
    opp_head_to_opp_body_overlap    = false;

    for (int col = 0; col < 5 && !hit; col++) {
        uint8_t head      = snake_head_bm[col];
        uint8_t body      = snake_body_bm[col];
        uint8_t opp_head  = opp_snake_head_bm[col];
        uint8_t opp_body  = opp_snake_body_bm[col];

        // exclude heads from their own bodies when checking self-collision
        uint8_t body_no_head     = body & ~head;
        uint8_t opp_body_no_head = opp_body & ~opp_head;

        user_head_opp_body_overlap   = (head     & opp_body_no_head) != 0;
        opp_head_user_body_overlap   = (opp_head & body_no_head)     != 0;
        head_to_head_overlap         = (head     & opp_head)         != 0;

        head_to_body_overlap         = overlap_snake_history(&snake_body_his, i, j);
        opp_head_to_opp_body_overlap = overlap_snake_history(&opp_snake_body_his, i_opp, j_opp);

        hit = user_head_opp_body_overlap || opp_head_user_body_overlap ||
              head_to_head_overlap || head_to_body_overlap || opp_head_to_opp_body_overlap;
    }

    if (hit) {
        
        game_running = false;
    if (user_head_opp_body_overlap) {
    // player head hit opponent body
    game_running = false;
    death_scenario = 1;
}

else if (opp_head_user_body_overlap) {
    // opponent head hit player body
    game_running = false;
    death_scenario = 2;
}

else if (head_to_head_overlap) {
    // both heads collided
    game_running = false;
    death_scenario = 3;

}

else if (head_to_body_overlap) {
    // player head hit its own body
    game_running = false;
    death_scenario = 4;
}

else if (opp_head_to_opp_body_overlap) {
    // opponent head hit its own body
    game_running = false;
    death_scenario = 5;
}

    }
}
 



