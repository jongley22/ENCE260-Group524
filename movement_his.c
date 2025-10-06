#include "movement_his.h"
#include <string.h> // for memmove
#include <stdbool.h>

void init_move_his(PairList *list) {
    list->num_pairs = 0;
}

static inline int clamp_max_pairs(int m) {
    if (m < 1)  return 1;
    if (m > 70) return 70;
    return m;
}

Pair addPair(PairList *list, int i, int j, int max_pairs) {
    Pair removed = (Pair){ -1, -1 };
    max_pairs = clamp_max_pairs(max_pairs);

    // If we're already at physical capacity, evict oldest to make room.
    if (list->num_pairs >= 70) {
        removed = list->tuple[0];
        memmove(&list->tuple[0], &list->tuple[1], (list->num_pairs - 1) * sizeof(Pair));
        list->num_pairs--;
    }

    // If we're at/over the per-call logical limit, evict oldest before inserting.
    if (list->num_pairs >= max_pairs) {
        removed = list->tuple[0];
        memmove(&list->tuple[0], &list->tuple[1], (list->num_pairs - 1) * sizeof(Pair));
        list->num_pairs--;
    }

    // Now safe to append.
    list->tuple[list->num_pairs].i = i;
    list->tuple[list->num_pairs].j = j;
    list->num_pairs++;

    return removed;
}

bool overlap_snake_history(PairList *list, int i, int j)
{
    for (int x = 0; x < 35; x++) { //only works for one matrice
        if ((list->tuple[x].i == i) && (list->tuple[x].j == j)) {
            return true;
        }
    }
    return false;
}


// void printList(const PairList *list, const Pair *old_tuple) {
//     printf("[ ");
//     for (int k = 0; k < list->num_pairs; k++) {
//         printf("(%d, %d) ", list->tuple[k].i, list->tuple[k].j);
//     }
//     printf("]");
//     if (old_tuple && (old_tuple->i != -1 || old_tuple->j != -1)) {
//         printf("  removed: (%d, %d)", old_tuple->i, old_tuple->j);
//     }
//     printf("\n");
// }





// #include "move_history_revised.h"

// int main(void) {
//     PairList list;
//     init_move_his(&list);

//     Pair r;

//     // Start with a logical limit of 3
//     r = addPair(&list, 1, 10, 3); printList(&list, &r);
//     r = addPair(&list, 2, 20, 3); printList(&list, &r);
//     r = addPair(&list, 3, 30, 3); printList(&list, &r);

//     // This insert enforces max_pairs=3, so it evicts (1,10)
//     r = addPair(&list, 4, 40, 3); printList(&list, &r);

//     // Bump the limit to 5 (still ≤ 70)
//     r = addPair(&list, 5, 50, 5); printList(&list, &r);
//     r = addPair(&list, 6, 60, 5); printList(&list, &r);

//     // Tighten back to 2 → evicts down to 1 slot before insert
//     r = addPair(&list, 7, 70, 2); printList(&list, &r);

//     return 0;
// }