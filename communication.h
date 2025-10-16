/*------------------------------------------------------------
 * File:        communication.h
 * Authors:     Maxwell Beran & Josh Ongley
 * Description: Header file for communication.c
 *------------------------------------------------------------*/

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    int i;
    int j;
    int i_opp;
    int j_opp;
} Coords;

/* Pack i and j (0–7 each) into one byte */
uint8_t pack_position(uint8_t x, uint8_t y);

/* Unpack one byte back into i and j */
void unpack_position(uint8_t packed, uint8_t *i, uint8_t *j);

Coords getCoords(void);


/* Update movement based on navswitch input and history */
void movement(void);

/* Handle IR send/receive and update opponent state */
void communication(void);

/* Send a “your turn” indicator over IR */
void send_turn(bool your_turn);


#endif 