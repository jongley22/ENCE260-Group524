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


PairList snake_body_his; //right now will be 1
PairList snake_head_his;

PairList opp_snake_body_his; //right now will be 1
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
    led_init();
    led_set (LED1, 0);

    
    // text initialising
    tinygl_init(PACER_RATE);
    // tinygl_font_set(&font5x7_1);
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
        game_finnished();
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
            static uint8_t scenario = 0;
            death_screen();
            led_while(); 
            led_set (LED1, 1);
            if (death_scenario == 1 || scenario == 129) {
                ir_uart_putc(0b10000001);
            } else if (death_scenario == 2 || scenario == 130) {
                ir_uart_putc(0b10000010);
            } else if (death_scenario == 3 || scenario == 132) {
                ir_uart_putc(0b10000100);
            } else if (death_scenario == 4 || scenario == 144) {
                ir_uart_putc(0b10010000);
            } else if (death_scenario == 5 || scenario == 160) {
                ir_uart_putc(0b10100000);
            }


            scenario = ir_uart_getc ();

            



          

            
      
        }
    }
}

