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
#include "final_message.h"
//include led.h


PairList snake_body_his; //right now will be 1
PairList snake_head_his;

PairList opp_snake_body_his; //right now will be 1
PairList opp_snake_head_his;
bool game_running = true; 



#define PACER_RATE 50
int main (void)
{
    srand(2232136546512532612535463512563615242532612535463321365);  // seed 
    system_init ();
    navswitch_init ();  
    led_init_custom();
    ir_uart_init ();
    led_init();

    pacer_init (PACER_RATE*5);

    tinygl_init(PACER_RATE);
    coord_generator();
    init_user_move_his(&snake_body_his);  // max 5 pairs (<=70) "snake_body extern declared in 
    init_user_move_his(&snake_head_his);

    init_opp_move_his(&opp_snake_body_his);  // max 5 pairs (<=70) "snake_body extern declared in 
    init_opp_move_his(&opp_snake_head_his);


    //while (1)
    while(game_running)
    {
    // apple_flasher();
    led_while(); 
    movement();
    communication();
    game_fin();
    // receive_turnn();   movement();
    if (navswitch_release_event_p (NAVSWITCH_PUSH)){
        coord_generator();
        }

    } if(!game_running) {

        final_message("DEATH");
        // if (user_head_opp_body_overlap){
        //      final_message("LOSE");
        // }
        // if (opp_head_user_body_overlap){
        //     final_message("WIN");
        // }
        // if (head_to_head_overlap){
        //     final_message("TIE");
        // }

    }
}

