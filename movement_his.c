/*------------------------------------------------------------
 * File:        movement_his.c
 * Authors:     Maxwell Beran & Josh Ongley
 * Description: Tracking snake movement history
 *              (head/body tuples), updating history and
 *              overlap checks against prior positions.
 *------------------------------------------------------------*/

#include "movement_his.h"
#include <string.h>   // for memmove
#include <stdbool.h>

/* Initialise player's movement history with a starting position */
void init_user_move_his(PairList *list)
{
    list->tuple[0].i = 3;
    list->tuple[0].j = 2;
    list->num_pairs = 1;
}

/* Initialise opponent's movement history as empty */
void init_opp_move_his(PairList *list)
{
    list->num_pairs = 0;
}

/* Clamp the caller-specified logical max_pairs to [1, 70] */
static inline int clamp_max_pairs(int m)
{
    if (m < 1)  return 1;
    if (m > 70) return 70;
    return m;
}

/* Append (i,j) to history, evicting the oldest when necessary; return evicted or {-1,-1} */
Pair addPair(PairList *list, int i, int j, int max_pairs)
{
    Pair removed = (Pair){ -1, -1 };
    max_pairs = clamp_max_pairs(max_pairs);

    /* If we're already at physical capacity, evict oldest to make room. */
    if (list->num_pairs >= 70) {
        removed = list->tuple[0];
        memmove(&list->tuple[0], &list->tuple[1], (list->num_pairs - 1) * sizeof(Pair));
        list->num_pairs--;
    }

    /* If we're at/over the per-call logical limit, evict oldest before inserting. */
    if (list->num_pairs >= max_pairs) {
        removed = list->tuple[0];
        memmove(&list->tuple[0], &list->tuple[1], (list->num_pairs - 1) * sizeof(Pair));
        list->num_pairs--;
    }

    /* Now safe to append. */
    list->tuple[list->num_pairs].i = i;
    list->tuple[list->num_pairs].j = j;
    list->num_pairs++;

    return removed;
}

/* Return true if (i,j) exists anywhere in the history */
bool overlap_snake_history(PairList *list, int i, int j)
{
    for (int x = 0; x < list->num_pairs; x++) {   // only works for one matrix
        if ((list->tuple[x].i == i) && (list->tuple[x].j == j)) {
            return true;
        }
    }
    return false;
}
