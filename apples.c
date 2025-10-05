#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "led_selector.h"
#include "apple.h"
// Do we have all these
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// pack the coords 
static uint8_t apple_counter = 0;
pacer_init (100);
void coord_generator(void) {
    
    if (navswitch_down_p (NAVSWITCH_PUSH)){
    srand(time(NULL));  // seed 
    int i = rand() % 7;  
    int j = rand() % 5;  
    apple_counter++;
    display_apple(i,j);
    }
    
}
void display_apple(i,j){
    led_selector(i,j,1);
    pacer_wait();
    led_selector(i,j,0);
    pacer_wait();
}


