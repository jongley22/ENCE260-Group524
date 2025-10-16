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
#include "final_message.h"
//include led.h


PairList snake_body_his; 
PairList snake_head_his;

PairList opp_snake_body_his; 
PairList opp_snake_head_his;

uint8_t game_running = 1;
uint8_t user_head_opp_body_overlap;
uint8_t opp_head_user_body_overlap;
uint8_t head_to_head_overlap;
uint8_t head_to_body_overlap;
uint8_t opp_head_to_opp_body_overlap;
uint8_t death_scenario;
#define MESSAGE_RATE 5
#define PACER_RATE 500
int main (void)
{
    srand(2232);  // seed 
    system_init ();

    navswitch_init ();  
    led_init_custom();
    ir_uart_init ();

    pacer_init (PACER_RATE);

    coord_generator();
    init_user_move_his(&snake_body_his); 
    init_user_move_his(&snake_head_his);

    init_opp_move_his(&opp_snake_body_his);  
    init_opp_move_his(&opp_snake_head_his);


    while (1)
    {
    // apple_flasher();
        Coords cord_status = getCoords();
        game_finnished(cord_status);
        static bool locked_out = false;
        
        if (game_running && (!locked_out)) {
            led_while(); 
            movement();
            apple_flasher();
            communication();
            // receive_turnn();   movement();
            if (navswitch_release_event_p (NAVSWITCH_PUSH)) {
                coord_generator();
            }
        

        }   
        if (!game_running) {
            locked_out = true;

            led_while(); 


            uint64_t buffer = 10;
            uint64_t max_tick = PACER_RATE / buffer;
            static uint64_t buf_ticker = 0;
            if (buf_ticker <= max_tick) {
                death_screen();
                buf_ticker++;
            } else {
                static bool send_once = true;
                if (send_once) {
                    ir_uart_putc(0b10000100);
                    send_once = false;
                }

                if (opp_head_to_opp_body_overlap) {
                    W_death_screen();
                } else if (head_to_head_overlap) {
                    W_death_screen();
                } else if (head_to_body_overlap) {
                    L_death_screen();
                } else if (user_head_opp_body_overlap) {
                    L_death_screen();
                } else if (opp_head_user_body_overlap) {
                    W_death_screen();
                } else if (death_scenario == 6) {
                    L_death_screen();
                }

            }
        }        
    }
}


            
      
