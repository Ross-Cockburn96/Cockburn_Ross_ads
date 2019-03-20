#ifndef MOVE_HISTORY_H
#include "state.h"
#define MOVE_HISTORY_H


struct moveHistory
{
    struct state *current_state;
    struct moveHistory *prev;
    struct moveHistory *next;
};
void display(struct moveHistory *);
void updateHistory(struct moveHistory**, struct state*);
void deepIntCopy(int **, int **);
void initialiseHistory(struct moveHistory **);
struct moveHistory *validateHistory(struct moveHistory**);







#endif
