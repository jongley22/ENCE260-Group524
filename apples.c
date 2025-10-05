#include "navswitch.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "apples.h"
#include "led_selector.h"


static uint8_t apple_counter = 1;

void coord_generator(void) {
    navswitch_update ();

    
    
    
    int app_i = rand() % 7;  
    int app_j = rand() % 5;  
    //int app_i = 1;  
    //int app_j = 1;  
    
    display_apple(app_i,app_j);
    
    
}
void display_apple(uint8_t i_display,uint8_t j_display){
    // pacer_init (100);
    // led_selector(i_display,j_display,1);
    // pacer_wait();
    // led_selector(i_display,j_display,0);
    // pacer_wait();
    apples_bm_sel(i_display,j_display,1);
    apple_counter++;

}

