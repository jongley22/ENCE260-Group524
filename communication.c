#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
    

system_init ();
navswitch_init ();

// pack the coords 



void movement()
{

navswitch_update ();

if (navswitch_push_event_p (NAVSWITCH_EAST)){
j++;
}

if (navswitch_push_event_p (NAVSWITCH_WEST)){
j--;
}
if (navswitch_push_event_p (NAVSWITCH_NORTH)){
i--;
}

if (navswitch_push_event_p (NAVSWITCH_SOUTH)){
i++;
}
uint8_t pack_position(uint8_t i, uint8_t j)
{
    return ((i & 0x07) << 3) | (j & 0x07);
}


if ((navswitch_push_event_p (NAVSWITCH_EAST))||(navswitch_push_event_p (NAVSWITCH_WEST))(navswitch_push_event_p (NAVSWITCH_SOUTH))||(navswitch_push_event_p (NAVSWITCH_WEST))){
    ir_uart_putc(coordinates); 
}
if (ir_uart_read_ready_p ()){
    opp_coords = ir_uart_getc ();
    // Unpack the coords
        void unpack_position(uint8_t packed, uint8_t *i, uint8_t *j)
    {
        *i = (packed >> 3) & 0x07;  // upper 3 bits
        *j = packed & 0x07;         // lower 3 bits

        // Call the bitmap update code to add oppisition to user 
        led_selector(i,j,1);  
        
    }
}


}