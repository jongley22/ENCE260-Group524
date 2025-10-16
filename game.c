/*------------------------------------------------------------
 * File:        game.c
 * Authors:     Maxwell Beran & Josh Ongley
 * Description: Main file, compiling snake operational functions.
 *------------------------------------------------------------*/

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

// Declaring user snake history to store i,j pairs
PairList snake_body_his; 
PairList snake_head_his;
PairList opp_snake_body_his; 
PairList opp_snake_head_his;

// Initialising game running
uint8_t game_running = 1;

// declaring overlap collision externs
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
    // random number generator
    srand(2232);  

    //initialising board utilities and drivers
    system_init ();
    navswitch_init ();  
    led_init_custom();
    ir_uart_init ();
    pacer_init (PACER_RATE);

    //generates intial apple coordinates 
    coord_generator();

    //initialising snake position history
    init_user_move_his(&snake_body_his); 
    init_user_move_his(&snake_head_his);
    init_opp_move_his(&opp_snake_body_his);  
    init_opp_move_his(&opp_snake_head_his);


    while (1)
    {
        //have any collisions between snake i,j and wall boundries
        Coords cord_status = getCoords();
        game_finnished(cord_status);

        static bool locked_out = false;
        
        // Running the game
        if (game_running && (!locked_out)) {
            // Keeps the matrix LEDs live
            led_while(); 
            
            
            movement();
            apple_flasher();
            communication();

            // spawning in apples
            if (navswitch_release_event_p (NAVSWITCH_PUSH)) {
                coord_generator();
            }
        

        }   
        // game no longer running, death screens
        if (!game_running) {
            locked_out = true;
            
            led_while(); 

            uint64_t buffer = 10;
            uint64_t max_tick = PACER_RATE / buffer;
            static uint64_t buf_ticker = 0;
            if (buf_ticker <= max_tick) {
                blank_screen();
                buf_ticker++;
            } else {
                static bool send_once = true;
                if (send_once) {
                    // Transmitting bit to tell oppisite screen game is over
                    ir_uart_putc(0b10000100);
                    send_once = false;
                }
                // all death scenarios
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


            
      
