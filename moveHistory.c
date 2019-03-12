#include "moveHistory.h"
#include "state.h"
#include <stdlib.h>
#include <stdio.h>

void display (struct moveHistory * history){
    while (history != NULL){
        printf("player who moved is %d" , history -> current_state -> player);
        history = history -> next;
    }
    
    
}

void updateHistory (struct moveHistory ** history, struct state * currentState) {
    struct moveHistory *temp, *current = *history;
    struct state *newState;
    newState = (struct state *) malloc (sizeof(struct state)); 
    newState -> player = currentState -> player;
    newState -> board = currentState -> board;
    if (*history == NULL){
        *history = (struct moveHistory *) malloc(sizeof(struct moveHistory));
        (*history) -> prev = NULL;
        (*history) -> current_state = newState;
        (*history) -> next = NULL;
    }
    else
    {
        while (current -> next != NULL){
        current = current -> next;
        }
        temp = (struct moveHistory *) malloc (sizeof(struct moveHistory));
        temp -> current_state = newState; 
        temp -> next = NULL;
        temp -> prev = current;
        current -> next = temp;
    }
    
    
}
