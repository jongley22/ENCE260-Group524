#include "system.h"
#include "pio.h"

/* Include the pacer module from the previous lab.
   You must have completed this before starting  this lab2-exercise.  */
#include "pacer.h"
#include "led_selector.h"
#include "tinygl.h"



#define PACER_RATE 50
int main (void)
{
    system_init ();
    

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
    }


    }
}

