#include "system.h"
#include "pio.h"
#include "navswitch.h"
#include "communication.h"
#include "pacer.h"
#include "led_selector.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "movement_his.h"
#include "apples.h"

PairList snake_body_his; //right now will be 1
PairList snake_head_his;

#define PACER_RATE 50
int main (void)
{
    srand(time(NULL));  // seed 
    system_init ();
    navswitch_init ();  
    led_init();
    ir_uart_init ();


    pacer_init (PACER_RATE*5);

    tinygl_init(PACER_RATE);
    coord_generator();
    init_move_his(&snake_body_his);  // max 5 pairs (<=70) "snake_body extern declared in 
    init_move_his(&snake_head_his);


    while (1)
    {
    
    led_while(); 
    movement();
    communication();
    
    if (navswitch_release_event_p (NAVSWITCH_PUSH)){
        coord_generator();
        }

    }
}

