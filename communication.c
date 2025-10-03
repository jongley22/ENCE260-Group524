#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "led_selector.h"
    

// pack the coords 
static uint8_t i = 3;
static uint8_t j = 2;

static uint8_t i_opp;
static uint8_t j_opp;


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
    
    navswitch_update ();
    if (navswitch_push_event_p (NAVSWITCH_EAST)) {
    j++;
    }
 
    if (navswitch_push_event_p (NAVSWITCH_WEST)) {
    j--;
    }

    if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
    i--;
    }

    if (navswitch_push_event_p (NAVSWITCH_SOUTH)){
    i++;
    }
    led_selector(i,j,1);
}

void communication(void)  
{
    
    uint8_t user_cords;
    uint8_t opp_coords;

    if ((navswitch_push_event_p (NAVSWITCH_EAST))||(navswitch_push_event_p (NAVSWITCH_WEST))||(navswitch_push_event_p (NAVSWITCH_SOUTH))||(navswitch_push_event_p (NAVSWITCH_WEST))){
            
  
        user_cords = pack_position(i,j);
        ir_uart_putc(user_cords); 
        //ir_uart_putc(i); 
    }
    if (ir_uart_read_ready_p ()){
        opp_coords = ir_uart_getc ();
        // Unpack the coords
        unpack_position(opp_coords, &i_opp, &j_opp);

    }
    //led_selector(i_opp,j_opp,1);
}


