#include "moveHistory.h"
#include "state.h"
#include "board.h"
#include <stdlib.h>
#include <stdio.h>



void display (struct moveHistory * history){
    printf("displaying...\n");
    int i,j;
    while (history != NULL){
        printf("player to move is %d\n" , history -> current_state -> player);
        for (int i = 0; i < 3; i++){
            printf("value of board is %d\n", **((history -> current_state -> board) +i));
            for (int j = 0; j < 3; j ++){
                printf("value of board is %d\n", *(*((history -> current_state -> board)+i)+j));
            }
        }
        printf ("-------------------------------\n");
        history = history -> prev;
    }
    
    
}

void initialiseHistory(struct moveHistory ** history){
    int **newBoard = NULL;
    struct state *newState;
    newState = (struct state *) malloc (sizeof(struct state)); 
    newState -> player = 1;
    (newState -> board) = initBoard(newBoard);

    *history = (struct moveHistory *) malloc(sizeof(struct moveHistory));
    (*history) -> prev = NULL;
    (*history) -> current_state = newState;
    (*history) -> next = NULL;
}

void updateHistory (struct moveHistory **history, struct state *currentState) {
    struct moveHistory *temp, *current = *history;
    struct state *newState;
    int i, j;
    int **newBoard = NULL;
    newState = (struct state *) malloc (sizeof(struct state)); 
    newState -> player = currentState -> player;
    (newState -> board) = initBoard(newBoard);
    deepIntCopy(newState -> board, currentState -> board);
    
    for (int i = 0; i < 3; i++){
        printf("newState is %d\n", **((newState -> board) +i));
        for (int j = 0; j < 3; j ++){
            printf("newState is %d\n", *(*((newState -> board)+i)+j));
        }
    }

    while (current -> next != NULL){ //ensure we are at the most recent move
    current = current -> next;
    }
    temp = (struct moveHistory *) malloc (sizeof(struct moveHistory));
    temp -> current_state = newState; 
    temp -> next = NULL;
    temp -> prev = current;
    current -> next = temp;
    *history = (*history) -> next; //point to the most recent move
}

//recursive function to prevent memory leak when overwriting history list
struct moveHistory *validateHistory(struct moveHistory ** history){
    int **histBoard = (*history)->current_state -> board;
    if ((*history)-> next == NULL){
        printf("next node is null\n");
        return (*history);
    }else{
        printf("next node is not null\n");
        freeBoard((*history) -> next -> current_state -> board);
        free((*history) -> next -> current_state);
        free(validateHistory((&((*history) -> next))));
        (*history) -> next = NULL;
        return (*history);
    }
}




void deepIntCopy(int **newBoard, int **oldBoard){
    int i,j;
     for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j ++){
            *(*(newBoard+i)+j) = *(*(oldBoard+i)+j); 
        }
    }
}

