#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"




    navswitch_update ();

        
    if (navswitch_push_event_p (NAVSWITCH_EAST)){
        j++;
    }
                

    if (navswitch_push_event_p (NAVSWITCH_WEST)){
        j--;
    }
    if (navswitch_push_event_p (NAVSWITCH_NORTH)){
        i--;
    }
                

    if (navswitch_push_event_p (NAVSWITCH_SOUTH)){
        i++;
    }
                       