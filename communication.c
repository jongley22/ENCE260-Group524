/*------------------------------------------------------------
 * File:        communication.c
 * Authors:     Maxwell Beran & Josh Ongley
 * Description: Communication between each board, packing snake coordinates and transmitting. Recieving coordinates and unpacking them. 
 *------------------------------------------------------------*/

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "led_selector.h"
#include "movement_his.h"
#include <stdbool.h>

// Pack the coords

static uint8_t i_opp;
static uint8_t j_opp;

static uint8_t i = 3;
static uint8_t j = 2;

static uint8_t snake_size = 1;
static uint8_t opp_snake_size = 1;

/* Packs x and y location into a single byte (3 bits each) */
uint8_t pack_position(uint8_t x_p, uint8_t y_p)  
{
    return ((x_p & 0x07) << 3) | (y_p & 0x07);
    snake_body_bm_sel(2, 3, 0);
}

/* Unpacks a packed byte back into x/y */
void unpack_position(uint8_t packed, uint8_t *x_unp, uint8_t *y_unp)
{
    if (packed & 0b10000000) {
        game_running = false;
    }

    // Mask to ignore the 4th bit of each nibble
    uint8_t high_nibble = (packed >> 3) & 0x0F;   // take 4 bits
    *x_unp = high_nibble & 0x07;                  // ignore top bit, only 0–7 range

    uint8_t low_nibble = packed & 0x0F;           // take 4 bits
    *y_unp = low_nibble & 0x07;                   // ignore top bit, only 0–7 range
} 

//packs up the coords for game_finnished 
Coords getCoords(void) {
    Coords c;

    c.i = i;
    c.j = j;
    c.i_opp = i_opp;
    c.j_opp = j_opp;  
    return c;
}

/* Reads navswitch input and updates local snake position/history */
void movement(void)
{
    uint8_t j_changed = 0, i_changed = 0;

    navswitch_update();

    if (navswitch_push_event_p(NAVSWITCH_EAST)) {
        if (j==4){
            death_scenario=6;
            game_running=false;
        }
        j++;
        j_changed = 1;
    }
    if (navswitch_push_event_p(NAVSWITCH_WEST)) {
        j--;
        j_changed = 1;
    }
    if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
        if (i==0){
            death_scenario=6;
            game_running=false;
        }
        i--;
        i_changed = 1;
    }
    if (navswitch_push_event_p(NAVSWITCH_SOUTH) && !(overlap_snake_history(&snake_body_his, i + 1, j))) {
        if (i==6){
            death_scenario=6;
            game_running=false;
        }
        i++;
        i_changed = 1;
    }

    if (i_changed || j_changed) {
        Pair overlap_cord;

        if (user_apple_eaten(&overlap_cord)) {
            snake_size++;
            apples_bm_sel(overlap_cord.i, overlap_cord.j, 0);
        }

        Pair body_ev = addPair(&snake_body_his, i, j, snake_size);
        Pair head_ev = addPair(&snake_head_his, i, j, 1);

        const Pair *body_old_tuple =
            (body_ev.i == -1 && body_ev.j == -1) ? NULL : &body_ev;

        const Pair *head_old_tuple =
            (head_ev.i == -1 && head_ev.j == -1) ? NULL : &head_ev;

        // if equal to -1 body is extending so if its not turn off last led body
        if (body_old_tuple && (body_old_tuple->i != -1 || body_old_tuple->j != -1)) {
            snake_body_bm_sel(body_old_tuple->i, body_old_tuple->j, 0);
        }

        if (head_old_tuple && (head_old_tuple->i != -1 || head_old_tuple->j != -1)) {
            snake_head_bm_sel(head_old_tuple->i, head_old_tuple->j, 0);
        }
    }
    j_changed = 0, i_changed = 0;
}

/* Handles IR receive/send and updates opponent/body bitmaps */
void communication(void)
{
    uint8_t user_cords;
    uint8_t opp_coords;
    uint8_t move_made = ((navswitch_push_event_p(NAVSWITCH_EAST)) || (navswitch_push_event_p(NAVSWITCH_NORTH)) ||
                         (navswitch_push_event_p(NAVSWITCH_SOUTH)) || (navswitch_push_event_p(NAVSWITCH_WEST)));
    Pair overlap_cord;

    if (ir_uart_read_ready_p()) {
        opp_coords = ir_uart_getc();
        unpack_position(opp_coords, &i_opp, &j_opp);
        // led_selector(6-i_opp,4-j_opp,1);

        if ((4 - j_opp) == 0) {
            opp_snake_size = 1;
        }

        if (opp_apple_eaten(&overlap_cord)) {
            opp_snake_size++;
            apples_bm_sel(overlap_cord.i, overlap_cord.j, 0);
        }

        Pair oppbody_ev = addPair(&opp_snake_body_his, 6 - i_opp, 4 - j_opp, opp_snake_size);
        Pair opphead_ev = addPair(&opp_snake_head_his, 6 - i_opp, 4 - j_opp, 1);

        const Pair *oppbody_old_tuple =
            (oppbody_ev.i == -1 && oppbody_ev.j == -1) ? NULL : &oppbody_ev;

        const Pair *oppp_head_old_tuple =
            (opphead_ev.i == -1 && opphead_ev.j == -1) ? NULL : &opphead_ev;

        // if equal to -1 body is extending so if it’s not, turn off last LED body
        if (oppbody_old_tuple && (oppbody_old_tuple->i != -1 || oppbody_old_tuple->j != -1)) {
            op_snake_body_bm_sel(oppbody_old_tuple->i, oppbody_old_tuple->j, 0);
        }

        if (oppp_head_old_tuple && (oppp_head_old_tuple->i != -1 || oppp_head_old_tuple->j != -1)) {
            op_snake_head_bm_sel(oppp_head_old_tuple->i, oppp_head_old_tuple->j, 0);
        }

        op_snake_head_bm_sel(6 - i_opp, 4 - j_opp, 1);
        op_snake_body_bm_sel(6 - i_opp, 4 - j_opp, 1);
    }

    if (j > 4 && move_made) {
        user_cords = pack_position(i, j - 3); 
        ir_uart_putc(user_cords);
    } else if (j < 4 && move_made) {
        user_cords = pack_position(i, j + 5); 
        ir_uart_putc(user_cords);
    } else {
        snake_body_bm_sel(i, j, 1);
        snake_head_bm_sel(i, j, 1);
        bitmap_complier();
    }
}

