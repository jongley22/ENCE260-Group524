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
#include "led.h"
#include "../fonts/font5x7_1.h"

//include led.h


PairList snake_body_his; //right now will be 1
PairList snake_head_his;

PairList opp_snake_body_his; //right now will be 1
PairList opp_snake_head_his;



#define MESSAGE_RATE 5
#define PACER_RATE 500
int main (void)
{
    srand(2232);  // seed 
    system_init ();

    navswitch_init ();  
    led_init_custom();
    ir_uart_init ();
    led_init();


    
    // text initialising
    tinygl_init(PACER_RATE);
    //tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);

    tinygl_text("WIN");

    pacer_init (PACER_RATE);
    
    
    
    coord_generator();
    init_user_move_his(&snake_body_his);  // max 5 pairs (<=70) "snake_body extern declared in 
    init_user_move_his(&snake_head_his);

    init_opp_move_his(&opp_snake_body_his);  // max 5 pairs (<=70) "snake_body extern declared in 
    init_opp_move_his(&opp_snake_head_his);


    while (1)
    {
    // apple_flasher();
    led_while(); 
    movement();
    communication();
    // receive_turnn();   movement();
    if (navswitch_release_event_p (NAVSWITCH_PUSH)){
        coord_generator();
        }

    }
}

