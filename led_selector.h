/*------------------------------------------------------------
 * File:        led_selector.h
 * Authors:     Maxwell Beran & Josh Ongley
 * Description: Header for LED matrix control, bitmap management,
 *              apple and collision logic for Slither.
 *------------------------------------------------------------*/

#ifndef LEDMAT_H
#define LEDMAT_H

#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "apples.h"
#include "movement_his.h"

/* Global variables */
extern uint8_t death_scenario;
extern uint8_t game_running;
extern uint8_t user_head_opp_body_overlap;
extern uint8_t opp_head_user_body_overlap;
extern uint8_t head_to_head_overlap;
extern uint8_t head_to_body_overlap;
extern uint8_t opp_head_to_opp_body_overlap;

/* Define PIO pins driving LED matrix rows and columns */
static const pio_t rows[7];
static const pio_t cols[5];

/* Display functions */
void display_column(uint8_t row_pattern, uint8_t current_column);
void led_while(void);
void led_init_custom(void);
void led_selector(uint8_t i, uint8_t j, uint8_t bol);
void bitmap_complier(void);

/* Bitmap setters */
void snake_head_bm_sel(uint8_t i, uint8_t j, uint8_t bol);
void apples_bm_sel(uint8_t i, uint8_t j, uint8_t bol);
void snake_body_bm_sel(uint8_t i, uint8_t j, uint8_t bol);
void op_snake_body_bm_sel(uint8_t i, uint8_t j, uint8_t bol);
void op_snake_head_bm_sel(uint8_t i, uint8_t j, uint8_t bol);

/* Apple logic */
void display_apple(uint8_t i_display, uint8_t j_display);
void coord_generator(void);
bool user_apple_eaten(Pair *out_pair);
bool opp_apple_eaten(Pair *out_pair);

/* Game state */
void game_finnished(void);
void death_screen(void);

#endif 
