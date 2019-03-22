#ifndef BOARD_H
#include "state.h"
#include "moveHistory.h"
#define BOARD_H

void printBoard(struct state *);
void initialiseState(struct state **);
void start(struct state **, struct moveHistory **);
int gameFinished(struct state *, int);
int checkRows(struct state *, int);
int checkColumns(struct state *, int);
int checkDiagonals(struct state *, int);
void rewindState(struct state **, struct moveHistory **);
void undo (struct state **, struct moveHistory **);
void redo (struct state**, struct moveHistory **);
int **initBoard(int **);
void freeBoard(int **);
void deepIntCopy(int **, int **);
void replayHistory(struct moveHistory *);


#endif
