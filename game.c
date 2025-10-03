
#include "system.h"
#include "pio.h"
#include "navswitch.h"

#include "pacer.h"
#include "led_selector.h"
#include "tinygl.h"



#define PACER_RATE 50
int main (void)
{
    system_init ();
    navswitch_init ();  
    

    int p1_i = 0; // row_player1
    int p1_j = 0; //col_player1
    int p2_i = 0; // row_player2
    int p2_j = 0; //col_player2



    pacer_init (PACER_RATE*5);

    tinygl_init(PACER_RATE);
    while (1)
    {
    
  

    led_init();
    

    while (1)
    {
    led_while(); 
    led_selector(0,0,1);        
    led_selector(0,4,1);   
    led_selector(6,0,1);    
    movement()    
    }


    }
}

