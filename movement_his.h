#ifndef MOVEMENT_HIS_H
#define MOVEMENT_HIS_H

#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int i;
    int j;
} Pair;

typedef struct {
    Pair tuple[20];   // fixed physical capacity
    int num_pairs;    // current count
} PairList;

extern PairList snake_body_his;
extern PairList snake_head_his;

extern PairList opp_snake_body_his;
extern PairList opp_snake_head_his;

void init_user_move_his(PairList *list);

void init_opp_move_his(PairList *list);

/**
 * Adds a pair (i, j) while enforcing a per-call maximum item count.
 * - max_pairs: desired logical max for THIS insert (clamped to [1, 70]).
 * - Returns the oldest removed pair if one was evicted; (-1, -1) otherwise.
 */
Pair addPair(PairList *list, int i, int j, int max_pairs);

bool overlap_snake_history(PairList *list, int i, int j);

// void printList(const PairList *list, const Pair *old_tuple);

#endif