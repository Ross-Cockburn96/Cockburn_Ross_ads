#ifndef MOVE_HISTORY_H
#include "state.h"
#define MOVE_HISTORY_H

void  display(struct moveHistory *);
void updateHistory(struct moveHistory**, struct state*);


struct moveHistory
{
    struct state *current_state;
    struct moveHistory *prev;
    struct moveHistory *next;
};



#endif
