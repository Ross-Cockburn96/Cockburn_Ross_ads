#ifndef STATE_H
#define STATE_H


//the state structure holds the game board and what player is playing the next move 
struct state
{
    int player;
    int **board;
};

#endif