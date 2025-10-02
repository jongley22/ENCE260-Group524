// /*
// Put your names, usernames, dates, description of the file etc here
// */


// #include "system.h"
// #include "pacer.h"
// #include "pio.h"

// int main (void)
// {
//     system_init ();


//     while (1)
//     {



//     }
// }


// #include "system.h"
// #include "pio.h"

// /* Include the pacer module from the previous lab.
//    You must have completed this before starting this lab2-exercise.  */
// #include "pacer.h"

// int main (void)
// {
//     system_init ();

//     pio_config_set (LEDMAT_ROW1_PIO, PIO_OUTPUT_HIGH);
//     pio_config_set (LEDMAT_ROW2_PIO, PIO_OUTPUT_HIGH);
//     pLED_ACTIVATOR(1,2);io_config_set (LEDMAT_ROW3_PIO, PIO_OUTPUT_HIGH);
//     pio_config_set (LEDMAT_ROW4_PIO, PIO_OUTPUT_HIGH);
//     pio_config_set (LEDMAT_ROW5_PIO, PIO_OUTPUT_HIGH);
//     pio_config_set (LEDMAT_ROW6_PIO, PIO_OUTPUT_HIGH);
//     pio_config_set (LEDMAT_ROW7_PIO, PIO_OUTPUT_HIGH);

//     pio_config_set (LEDMAT_COL1_PIO, PIO_OUTPUT_HIGH);
    
//     pio_config_set (LEDMAT_COL2_PIO, PIO_OUTPUT_HIGH);

//     pio_config_set (LEDMAT_COL3_PIO, PIO_OUTPUT_HIGH);

//     pio_config_set (LEDMAT_COL4_PIO, PIO_OUTPUT_HIGH);
//     pio_config_set (LEDMAT_COL5_PIO, PIO_OUTPUT_HIGH);
//     /* TODO: Initialise the pins of the LED matrix.  */
    

//     /* Set up pacer with a frequency of 100 Hz.  
//         This gives 50Hz alternating between the 2 states.*/
//     pacer_init (37000);
//     while (1)
//     {
//         /* Pace the loop.  */
//         pacer_wait ();

//         pio_output_low(LEDMAT_COL5_PIO);
//         pio_output_low(LEDMAT_COL1_PIO);
//         pio_output_low(LEDMAT_ROW1_PIO);
//         pio_output_high(LEDMAT_ROW7_PIO);

//         pacer_wait ();

//         // col 5 stays on always
//         pio_output_low(LEDMAT_ROW7_PIO);
//         pio_output_high(LEDMAT_COL1_PIO);
//         pio_output_high(LEDMAT_ROW1_PIO); 
//         /* TODO: Drive the LED matrix using the pio functions,
//            displaying only three corner LEDs.  */
//     }
// }

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

    // pio_config_set (LEDMAT_ROW1_PIO, PIO_OUTPUT_HIGH);
    // pio_config_set (LEDMAT_ROW2_PIO, PIO_OUTPUT_HIGH);
    // pio_config_set (LEDMAT_ROW3_PIO, PIO_OUTPUT_HIGH);
    // pio_config_set (LEDMAT_ROW4_PIO, PIO_OUTPUT_HIGH);
    // pio_config_set (LEDMAT_ROW5_PIO, PIO_OUTPUT_HIGH);
    // pio_config_set (LEDMAT_ROW6_PIO, PIO_OUTPUT_HIGH);
    // pio_config_set (LEDMAT_ROW7_PIO, PIO_OUTPUT_HIGH);

    // pio_config_set (LEDMAT_COL1_PIO, PIO_OUTPUT_HIGH);
    
    // pio_config_set (LEDMAT_COL2_PIO, PIO_OUTPUT_HIGH);

    // pio_config_set (LEDMAT_COL3_PIO, PIO_OUTPUT_HIGH);

    // pio_config_set (LEDMAT_COL4_PIO, PIO_OUTPUT_HIGH);
    // pio_config_set (LEDMAT_COL5_PIO, PIO_OUTPUT_HIGH);

    

    pacer_init (PACER_RATE*5);

    tinygl_init(PACER_RATE);
    while (1)
    {
    
    //     // pacer_wait();
    //     // LED_ACTIVATOR(3,4);
    //     // /* Pace the loop.  */



    //     // pacer_wait ();

    //     // // col 5 stays on always
    //     // pio_output_low(LEDMAT_ROW1_PIO);
    //     // pio_output_low(LEDMAT_COL1_PIO);
    //     // pio_output_high(LEDMAT_ROW7_PIO); 
    //     // pio_output_low(LEDMAT_COL5_PIO);
    //     // /* TODO: Drive the LED matrix using the pio functions,
    //     //    displaying only three corner LEDs.  */
        
    //     // pacer_wait ();
    //     // pio_output_low(LEDMAT_ROW7_PIO);
    //     // pio_output_high(LEDMAT_COL5_PIO);


    //     // pacer_wait();
    //     // tinygl_clear ();
        
    //     // tinygl_point_t pixel_pos;
    //     //     pixel_pos.x = 1;
    //     //     pixel_pos.y = 5;
    //     // tinygl_pixel_set (pixel_pos, 1);
    //     // tinygl_update ();

    //     // pacer_wait();
    //     // tinygl_clear ();
    //     // tinygl_point_t pixeel_pos;
    //     //     pixeel_pos.x = 1;
    //     //     pixeel_pos.y = 1;
    //     // tinygl_pixel_set (pixeel_pos, 1);
    //     // tinygl_update ();
        
    //     pacer_wait();
    //     tinygl_clear ();
    //     tinygl_point_t pixeeel_pos;
    //         pixeeel_pos.x = 1;
    //         pixeeel_pos.y = 1;
    //     tinygl_pixel_set (pixeeel_pos, 1);
    //     tinygl_update ();

    // // pacer_wait();
    // // LED_ACTIVATOR(0,0);
    // // pacer_wait();
    // // LED_ACTIVATOR(0,4);
    // // pacer_wait();
    // // LED_ACTIVATOR(6,0);

    led_init();
    

    while (1)
    {
    led_while();         
    }


    }
}

