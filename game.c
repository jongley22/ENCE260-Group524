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
//     pio_config_set (LEDMAT_ROW3_PIO, PIO_OUTPUT_HIGH);
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

#define PACER_RATE 100
int main (void)
{
    system_init ();

    pio_config_set (LEDMAT_ROW1_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_ROW2_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_ROW3_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_ROW4_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_ROW5_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_ROW6_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_ROW7_PIO, PIO_OUTPUT_HIGH);

    pio_config_set (LEDMAT_COL1_PIO, PIO_OUTPUT_HIGH);
    
    pio_config_set (LEDMAT_COL2_PIO, PIO_OUTPUT_HIGH);

    pio_config_set (LEDMAT_COL3_PIO, PIO_OUTPUT_HIGH);

    pio_config_set (LEDMAT_COL4_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_COL5_PIO, PIO_OUTPUT_HIGH);

    

    pacer_init (PACER_RATE);
    while (1)
    {
        // /* Pace the loop.  */



        // pacer_wait ();

        // // col 5 stays on always
        // pio_output_low(LEDMAT_ROW1_PIO);
        // pio_output_low(LEDMAT_COL1_PIO);
        // pio_output_high(LEDMAT_ROW7_PIO); 
        // pio_output_low(LEDMAT_COL5_PIO);
        // /* TODO: Drive the LED matrix using the pio functions,
        //    displaying only three corner LEDs.  */
        
        // pacer_wait ();
        // pio_output_low(LEDMAT_ROW7_PIO);
        // pio_output_high(LEDMAT_COL5_PIO);
        LED1_1(1);
        pacer_wait();
        LED1_5(1);
        pacer_wait();
        LED1_7(1);
        pacer_wait();


    }
}

