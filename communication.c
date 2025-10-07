#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "led_selector.h"
#include "movement_his.h"
#include <stdbool.h>
#include "led.h"
#define TURN_HEADER 0xF0  // 1111 0000

// pack the coords 


static uint8_t i_opp;
static uint8_t j_opp;

static uint8_t opp_snake_size;

static uint8_t i = 3;
static uint8_t j = 2;

static uint8_t snake_size = 1;


// static  bool turn = false;

// static bool first_turn = true;

// void receive_turnn(void);

// void send_turn(bool your_turn);


uint8_t pack_position(uint8_t x_p, uint8_t y_p) //different from i and j
{
    return ((x_p & 0x07) << 3) | (y_p & 0x07);snake_body_bm_sel(2,3,0);
}

uint8_t pack_size(uint8_t size)
{
    return (0xB0 | (size & 0x0F));
}

void unpack_position(uint8_t packed, uint8_t *x_unp, uint8_t *y_unp, uint8_t *size)
{
    uint8_t high_nibble = (packed >> 4) & 0x0F;
    uint8_t low_nibble = packed & 0x0F;

    if (high_nibble == 0x0B)  // If upper nibble is 0xB (1011), it's a size value
    {
        *size = low_nibble;
        // Don't touch x_unp or y_unp
    }
    else
    {
        *x_unp = high_nibble;
        *y_unp = low_nibble;
        // Don't touch size
    }
}

void movement(void)
{
    uint8_t j_changed = 0, i_changed = 0;



    navswitch_update();
    // if (first_turn || turn) {    

    // led_set (LED1, 1);

        if (navswitch_push_event_p(NAVSWITCH_EAST) && !(overlap_snake_history(&snake_body_his, i, j+1))) { 
            j++; 
            j_changed = 1; 
        }
        if (navswitch_push_event_p(NAVSWITCH_WEST) && !(overlap_snake_history(&snake_body_his, i, j-1))) { 
            j--; 
            j_changed = 1; 
        }
        if (navswitch_push_event_p(NAVSWITCH_NORTH) && !(overlap_snake_history(&snake_body_his, i-1, j))) { 
            i--; 
            i_changed = 1; 
        }
        if (navswitch_push_event_p(NAVSWITCH_SOUTH) && !(overlap_snake_history(&snake_body_his, i+1, j))) { 
            i++; 
            i_changed = 1; 
        }

    if (i_changed || j_changed) {
        // first_turn = false;   // after the very first move, rely on IR packets
        // apples_bm_sel(0,0,1);
        

        // Showing it's no longer your turn 

        
        Pair overlap_cord;

        if (apple_eaten(&overlap_cord)) {
            snake_size++;
            apples_bm_sel(overlap_cord.i, overlap_cord.j, 0);
        }
        Pair body_ev = addPair(&snake_body_his, i, j, snake_size);
        Pair head_ev = addPair(&snake_head_his, i, j, 1);

        // Turn the value into an "optional pointer":
        // NULL means "no eviction"; otherwise points to body_ev.
        const Pair *body_old_tuple =
            (body_ev.i == -1 && body_ev.j == -1) ? NULL : &body_ev;
 
        //now head
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

void communication(void) 
{
    // receive_turnn();
    uint8_t user_cords;
    uint8_t user_size;

    uint8_t opp_info;
    uint8_t move_made = ((navswitch_push_event_p (NAVSWITCH_EAST))||(navswitch_push_event_p (NAVSWITCH_WEST))||
                        (navswitch_push_event_p (NAVSWITCH_SOUTH))||(navswitch_push_event_p (NAVSWITCH_WEST)));

    // if ((navswitch_push_event_p (NAVSWITCH_EAST))||(navswitch_push_event_p (NAVSWITCH_WEST))||(navswitch_push_event_p (NAVSWITCH_SOUTH))||(navswitch_push_event_p (NAVSWITCH_WEST))){
            
  
    //     user_cords = pack_position(i,j);
    //     ir_uart_putc(user_cords); 
    
    // }

    // if (move_made){
    //     send_turn(true);
    //     led_set (LED1, 0);

    // }

    if (ir_uart_read_ready_p ()) { //reciver
        opp_info = ir_uart_getc ();
        unpack_position(opp_info, &i_opp, &j_opp, &opp_snake_size);
        led_selector(6-i_opp,4-j_opp,1);

        Pair oppbody_ev = addPair(&opp_snake_body_his, 6-i_opp, 4-j_opp, 2);
        Pair opphead_ev = addPair(&opp_snake_head_his, 6-i_opp, 4-j_opp, 1);

        // Turn the value into an "optional pointer":
        // NULL means "no eviction"; otherwise points to oppbody_ev.
        const Pair *oppbody_old_tuple =
            (oppbody_ev.i == -1 && oppbody_ev.j == -1) ? NULL : &oppbody_ev;

        // now head
        const Pair *oppp_head_old_tuple =
            (opphead_ev.i == -1 && opphead_ev.j == -1) ? NULL : &opphead_ev;

        // if equal to -1 body is extending so if it’s not, turn off last LED body
        if (oppbody_old_tuple && (oppbody_old_tuple->i != -1 || oppbody_old_tuple->j != -1)) {
            snake_body_bm_sel(oppbody_old_tuple->i, oppbody_old_tuple->j, 0);
        }

        if (oppp_head_old_tuple && (oppp_head_old_tuple->i != -1 || oppp_head_old_tuple->j != -1)) {
            snake_head_bm_sel(oppp_head_old_tuple->i, oppp_head_old_tuple->j, 0);
        }


    }

    if (j>4 && move_made) {
        user_cords = pack_position(i,j-3);
        // user_size = pack_size(snake_size);
        ir_uart_putc(user_cords); 
        // ir_uart_putc(user_size);  //can I do this 

    } else  {
        snake_body_bm_sel(i,j,1);
        snake_head_bm_sel(i,j,1); 
        bitmap_complier();
        
    }
   
}

// --------- Send whose turn it is ---------
// void send_turn(bool your_turn)
// {
//     uint8_t packet = TURN_HEADER | (your_turn ? 0x01 : 0x00);
//     ir_uart_putc(packet);
// }

// --------- Receive and decode ---------
// Returns true if it's YOUR turn, false otherwise.
// If no turn packet available, returns false.
// void receive_turnn(void)
// {
//     uint8_t val = ir_uart_getc();
//     if ((val & 0xF0) == TURN_HEADER) {
//         first_turn = false;
//         turn = (val & 0x01) != 0;
//         return;
//     }
//     turn = false;
//     return;
// }

