/*------------------------------------------------------------
 * File:        movement_his.h
 * Authors:     Maxwell Beran & Josh Ongley
 * Description: Header for tracking snake movement history.
 *              Defines Pair and PairList structures and
 *              provides functions for managing movement
 *              history and overlap detection.
 *------------------------------------------------------------*/

#ifndef MOVEMENT_HIS_H
#define MOVEMENT_HIS_H

#include <stdio.h>
#include <stdbool.h>

/* Represents a single grid coordinate (i, j) */
typedef struct {
    int i;
    int j;
} Pair;

/* Stores a list of past movement coordinates */
typedef struct {
    Pair tuple[20];   // fixed physical capacity
    int num_pairs;    // current count
} PairList;

/* Extern declarations for both player and opponent movement histories */
extern PairList snake_body_his;
extern PairList snake_head_his;
extern PairList opp_snake_body_his;
extern PairList opp_snake_head_his;

/* Initialise player and opponent movement histories */
void init_user_move_his(PairList *list);
void init_opp_move_his(PairList *list);

/* Adds a pair (i, j) while enforcing a per-call maximum item count.
 * - max_pairs: desired logical max for THIS insert (clamped to [1, 70]).
 * - Returns the oldest removed pair if one was evicted; (-1, -1) otherwise.
 */
Pair addPair(PairList *list, int i, int j, int max_pairs);

/* Checks if a given (i, j) position already exists in the movement history */
bool overlap_snake_history(PairList *list, int i, int j);

#endif 
