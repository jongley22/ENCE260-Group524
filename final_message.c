#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"


#define PACER_RATE 500
#define MESSAGE_RATE 5

int main (void)
{
    system_init();

    /* TODO: Initialise tinygl. */

    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);


    // Only line to chage - if statement based on who died
    tinygl_text("WIN");



    /* TODO: Set the message using tinygl_text().  */
    

    pacer_init (PACER_RATE);

    while(1)
    {
        pacer_wait();
        tinygl_update();
        /* TODO: Call the tinygl update function. */
        
    }
    return 0;
}
