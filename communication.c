#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "led_selector.h"
#include "movement_his.h"
    

// pack the coords 


static uint8_t i_opp;
static uint8_t j_opp;

static uint8_t i = 3;
static uint8_t j = 2;



uint8_t pack_position(uint8_t x_p, uint8_t y_p) //different from i and j
{
    return ((x_p & 0x07) << 3) | (y_p & 0x07);
}

void unpack_position(uint8_t packed, uint8_t *x_unp, uint8_t *y_unp) // input pointer
{
    *x_unp = (packed >> 3) & 0x07;  // upper 3 bits change me value of pointer
    *y_unp = packed & 0x07;
          // lower 3 bits
}

void movement(void)
{

    uint8_t j_changed;
    uint8_t i_changed;
    navswitch_update ();
    Pair led_off;

    if (navswitch_push_event_p (NAVSWITCH_EAST)) {
        j++;
        j_changed = 1;
    }
 
    if (navswitch_push_event_p (NAVSWITCH_WEST)) {
        j--;
        j_changed = 1;
    }

    if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
        i--;
        i_changed = 1;
    }

    if (navswitch_push_event_p (NAVSWITCH_SOUTH)){
        i++;
        i_changed = 1;
    }

    if ((i_changed) || (j_changed)) {
        led_off = addPair(&snake_body, i, j, 4); //snake body is an extern declared in movement_his.h
        if (led_off.i != -1 || led_off.j != -1) {
            snake_head_bm_sel(led_off.i, led_off.j, 0);
        }

    }

}

void communication(void)  
{
    
    uint8_t user_cords;
    uint8_t opp_coords;
    uint8_t move_made = ((navswitch_push_event_p (NAVSWITCH_EAST))||(navswitch_push_event_p (NAVSWITCH_WEST))||
                        (navswitch_push_event_p (NAVSWITCH_SOUTH))||(navswitch_push_event_p (NAVSWITCH_WEST)));

    // if ((navswitch_push_event_p (NAVSWITCH_EAST))||(navswitch_push_event_p (NAVSWITCH_WEST))||(navswitch_push_event_p (NAVSWITCH_SOUTH))||(navswitch_push_event_p (NAVSWITCH_WEST))){
            
  
    //     user_cords = pack_position(i,j);
    //     ir_uart_putc(user_cords); 
    
    // }

    if (ir_uart_read_ready_p ()){
        opp_coords = ir_uart_getc ();
        unpack_position(opp_coords, &i_opp, &j_opp);
        led_selector(6-i_opp,4-j_opp,1);

    }

    if (j>4 && move_made) {
        user_cords = pack_position(i,j-3);
        ir_uart_putc(user_cords); 

    } else {
        snake_head_bm_sel(i,j,1);
        bitmap_complier();

    }
   
}


