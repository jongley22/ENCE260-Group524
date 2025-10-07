#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdint.h>
#include <stdbool.h>

/* Pack i and j (0–7 each) into one byte */
uint8_t pack_position(uint8_t x, uint8_t y);

/* Unpack one byte back into i and j */
void unpack_position(uint8_t packed, uint8_t *i, uint8_t *j);

/* Update movement based on navswitch input and send/receive over IR */
void movement(void);

void communication(void);

// void receive_turnn(void);

void send_turn(bool your_turn);
#endif