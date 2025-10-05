#ifndef APPLE_H
#define APPLE_H

#include <stdint.h>
#include <stdbool.h>

// Initialise apple system (seed RNG etc.)
void coord_generator(void);

// Generate a new random apple position
void display_apple(void);


#endif // APPLE_H