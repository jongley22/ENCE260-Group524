/*------------------------------------------------------------
 * File:        led_selector.c
 * Authors:     Maxwell Beran & Josh Ongley
 * Description: LED matrix driving, snake/opp/apple bitmaps,
 *              bitmap composition, and collision checks.
 *------------------------------------------------------------*/

#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "led_selector.h"
#include "apples.h"
#include "movement_his.h"

extern bool game_running;
bool user_head_opp_body_overlap = false;
bool opp_head_user_body_overlap = false;
bool head_to_head_overlap = false;

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

/** declaring and intialising bitmaps for each object in the game */

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

/* Drives one column of the LED matrix using row bit pattern */
void display_column(uint8_t row_pattern, uint8_t current_column)
{
    static uint8_t prev_col = 0;            // statics retain value between calls
    pio_output_high(cols[prev_col]);        // turn previous column off

    for (uint8_t i = 0; i < 7; i++) {
        uint8_t current_row = i;

        if ((row_pattern >> current_row) & 1) {
            pio_output_low(rows[current_row]);
        } else {
            pio_output_high(rows[current_row]);
        }
    }

    pio_output_low(cols[current_column]);
    prev_col = current_column;
}

/* Initialises LED matrix I/O and pacer timing */
void led_init_custom(void)
{
    system_init();
    pacer_init(500);

    /* Initialise LED matrix pins. */
    for (uint8_t i = 0; i < 7; i++) {
        pio_config_set(rows[i], PIO_OUTPUT_HIGH);
    }
    for (uint8_t i = 0; i < 5; i++) {
        pio_config_set(cols[i], PIO_OUTPUT_HIGH);
    }
}

/* Pacer wait and advance scan to the next column */
void led_while(void)
{
    pacer_wait();
    display_column(display_bitmap[current_column], current_column);

    current_column++;
    if (current_column > (LEDMAT_COLS_NUM - 1)) {
        current_column = 0;
    }
}

/* Computes collision masks and sets game over if any hit */
void game_fin(void)
{
    uint8_t uo_mask = 0, ou_mask = 0, hh_mask = 0;

    for (int col = 0; col < 5; col++) {
        uo_mask |= (snake_head_bm[col] & opp_snake_body_bm[col]);
        ou_mask |= (opp_snake_head_bm[col] & snake_body_bm[col]);
        hh_mask |= (snake_head_bm[col] & opp_snake_head_bm[col]);
    }

    user_head_opp_body_overlap = (uo_mask != 0);
    opp_head_user_body_overlap = (ou_mask != 0);
    head_to_head_overlap = (hh_mask != 0);

    if (user_head_opp_body_overlap || opp_head_user_body_overlap || head_to_head_overlap) {
        game_running = false;
    }
}

/* Sets or clears a single LED in the led_bm led bitmap */
void led_selector(uint8_t i, uint8_t j, uint8_t bol)
{
    if (i < 7 && j < 5) {                    // Validate indices
        if (bol) {
            led_bm[j] |= (1 << i);           // set bit
        } else {
            led_bm[j] &= ~(1 << i);          // clear bit
        }
    }
}

/* Sets or clears a pixel in the snake head bitmap */
void snake_head_bm_sel(uint8_t i, uint8_t j, uint8_t bol)
{
    if (i < 7 && j < 5) { 
{
    if (i < 7 && j < 5) {                     // Validate indices
        if (bol) {
            snake_head_bm[j] |= (1 << i);     // set bit
        } else {
            snake_head_bm[j] &= ~(1 << i);    // clear bit
        }
    }
}
        if (bol) {
            snake_head_bm[j] |= (1 << i);     // set bit
        } else {
            snake_head_bm[j] &= ~(1 << i);    // clear bit
        }
    }
}

/* Sets or clears a pixel in the snake body bitmap */
void snake_body_bm_sel(uint8_t i, uint8_t j, uint8_t bol)
{
    if (i < 7 && j < 5) {                     // Validate indices
        if (bol) {
            snake_body_bm[j] |= (1 << i);     // set bit
        } else {
            snake_body_bm[j] &= ~(1 << i);    // clear bit
        }
    }
}

/* Sets or clears a pixel in the opponent body bitmap */
void op_snake_body_bm_sel(uint8_t i, uint8_t j, uint8_t bol)
{
    if (i < 7 && j < 5) {                     // Validate indices
        if (bol) {
            opp_snake_body_bm[j] |= (1 << i); // set bit
        } else {
            opp_snake_body_bm[j] &= ~(1 << i);// clear bit
        }
    }
}

/* Sets or clears a pixel in the opponent head bitmap */
void op_snake_head_bm_sel(uint8_t i, uint8_t j, uint8_t bol)
{
    if (i < 7 && j < 5) {                     // Validate indices
        if (bol) {
            opp_snake_head_bm[j] |= (1 << i); // set bit
        } else {
            opp_snake_head_bm[j] &= ~(1 << i);// clear bit
        }
    }
}

/* Sets or clears a pixel in the apples bitmap */
void apples_bm_sel(uint8_t i, uint8_t j, uint8_t bol)
{
    if (i < 7 && j < 5) {                     // Validate indices
        if (bol) {
            apples_on_bm[j] |= (1 << i);      // set bit
        } else {
            apples_on_bm[j] &= ~(1 << i);     // clear bit
        }
    }
}

/* Returns true if player head overlaps an apple; outputs the coord */
bool user_apple_eaten(Pair *out_pair)
{
    for (int j = 0; j < 5; j++) {             // each column
        uint8_t overlap = snake_head_bm[j] & apples_on_bm[j];
        if (overlap != 0) {                   // found overlap in this column
            for (int i = 0; i < 8; i++) {     // test each bit
                if (overlap & (1 << i)) {
                    out_pair->i = i;
                    out_pair->j = j;
                    return true;
                }
            }
        }
    }
    return false;                              // no overlap
}

/* Returns true if opponent head overlaps an apple; outputs the coord */
bool opp_apple_eaten(Pair *out_pair)
{
    for (int j = 0; j < 5; j++) {             // each column
        uint8_t overlap = opp_snake_head_bm[j] & apples_on_bm[j];
        if (overlap != 0) {                   // found overlap in this column
            for (int i = 0; i < 8; i++) {     // test each bit
                if (overlap & (1 << i)) {
                    out_pair->i = i;
                    out_pair->j = j;
                    return true;
                }
            }
        }
    }
    return false;                              // no overlap
}

/* Composes the display bitmap from all component layers */
void bitmap_complier(void)
{
    for (uint8_t j_search = 0; j_search < 5; j_search++) {
        display_bitmap[j_search] =
            snake_body_bm[j_search] | snake_head_bm[j_search] | apples_on_bm[j_search] |
            opp_snake_body_bm[j_search] | opp_snake_head_bm[j_search] | hiden_zone_bm[j_search];
    }
}

/* Clears the display to blank (all off) */
void death_screen(void)
{
    for (uint8_t j_search = 0; j_search < 5; j_search++) {
        display_bitmap[j_search] = blank_bm[j_search];
    }
}

/* Determines collisions this tick and sets death_scenario and game end */
void game_finnished(void)
{
    bool hit = false;

    // reset flags for this tick
    user_head_opp_body_overlap = false;
    opp_head_user_body_overlap = false;
    head_to_head_overlap = false;
    head_to_body_overlap = false;
    opp_head_to_opp_body_overlap = false;

    for (int col = 0; col < 5 && !hit; col++) {
        uint8_t head = snake_head_bm[col];
        uint8_t body = snake_body_bm[col];
        uint8_t opp_head = opp_snake_head_bm[col];
        uint8_t opp_body = opp_snake_body_bm[col];

        // exclude heads from their own bodies when checking self-collision
        uint8_t body_no_head = body & ~head;
        uint8_t opp_body_no_head = opp_body & ~opp_head;

        user_head_opp_body_overlap   = (head     & opp_body_no_head) != 0;
        opp_head_user_body_overlap   = (opp_head & body_no_head)     != 0;
        head_to_head_overlap         = (head     & opp_head)         != 0;
        head_to_body_overlap         = (head     & body_no_head)     != 0;
        opp_head_to_opp_body_overlap = (opp_head & opp_body_no_head) != 0;

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

        if (opp_head_user_body_overlap) {
            // opponent head hit player body
            game_running = false;
            death_scenario = 2;
        }

        if (head_to_head_overlap) {
            // both heads collided
            game_running = false;
            death_scenario = 3;
        }

        if (head_to_body_overlap) {
            // player head hit its own body
            game_running = false;
            death_scenario = 4;
        }

        if (opp_head_to_opp_body_overlap) {
            // opponent head hit its own body
            game_running = false;
            death_scenario = 5;
        }
    }
}
