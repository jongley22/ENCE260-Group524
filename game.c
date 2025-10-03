#include "system.h"
#include "pio.h"
#include "navswitch.h"
#include "communication.h"
#include "pacer.h"
#include "led_selector.h"
#include "tinygl.h"



#define PACER_RATE 50
int main (void)
{
    system_init ();
    navswitch_init ();  



    pacer_init (PACER_RATE*5);

    tinygl_init(PACER_RATE);
    while (1)
    {
    led_init();
    

    while (1)
    {
    led_while(); 
    movement();
    communication();
    }


    }
}

