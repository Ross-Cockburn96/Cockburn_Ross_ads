#include <stdlib.h>
#include <stdio.h>
#include "state.h"
#include "board.h"
#include "minMax.h"

#define HUMAN 1
#define AI 2
extern int boardSize;
int count = 0;
struct state * minmax(struct state *gameState, int player){
    count++;
    // if (count == 20){
    //     return NULL;
    // }
    int **gameBoard = gameState -> board;
    for (int i =0; i < boardSize; i++){
        for (int j = 0; j <boardSize; j++){
            printf("%d ", gameBoard[i][j]);
        }
    }
    int emptySpace = 0;
    
    for (int i=0; i<boardSize; i++){
        for (int j=0; j<boardSize; j++){
            if (gameBoard[i][j] == 0){
                // printf("getting here\n");
                // int **temp = NULL;
                // temp = realloc(boardSpaceCoords, (emptySpace +1) *sizeof(int*));
                // if (temp == NULL){
                //     printf("realloc failed\n");
                // }else{
                //     boardSpaceCoords = temp;
                // }
                // boardSpaceCoords[emptySpace] = (int*) malloc (2 * sizeof(int));
                // boardSpaceCoords[emptySpace][0] = i+1;
                // boardSpaceCoords[emptySpace][1] = j+1;
                emptySpace++;
            }
        }
    }
    int **boardSpaceCoords = (int**)malloc(emptySpace * sizeof(int*));
    int counter = 0;
    for (int i=0; i<boardSize; i++){
        for (int j=0; j<boardSize; j++){
            if (gameBoard[i][j] == 0){
                boardSpaceCoords[counter] = (int*) malloc(2*sizeof(int));
                boardSpaceCoords[counter][0] = i+1;
                boardSpaceCoords[counter][1] = j+1;
                counter ++;
            }
        }
    }
    printf("\n%d empty spaces\n", emptySpace);
    for (int i = 0; i < emptySpace; i ++){
            printf("free space at %d %d\n", boardSpaceCoords[i][0], boardSpaceCoords[i][1] );
    }

    if (gameFinished(gameState, HUMAN) == 1){
        printf("human won bad move\n");
        gameState -> score = -1;
        return gameState;
    }else{
        if (gameFinished(gameState, AI) ==1){
            printf("AI won good move\n");
            gameState -> score = 1;
            return gameState;
        }else{
            if (emptySpace == 0){
                printf("DRAW\n");
                gameState -> score = 0;
                return gameState;
            }
        }
    }

    struct state **states;
    states = (struct state **) malloc (sizeof(struct state *));
    //for each space on the board that is empty, try placing a marker on it
    struct state * result = (struct state *) malloc (sizeof(struct state));
    for (int i = 0; i < emptySpace; i++){
        int **newBoard = NULL;
        states[i] = (struct state *) malloc (sizeof(struct state));
        states[i] -> board = initBoard(newBoard);
        deepIntCopy(states[i] -> board, gameBoard);
        int row = boardSpaceCoords[i][0];
        int column = boardSpaceCoords[i][1];

        states[i] -> board[row-1][column-1] = player;

        if (player == AI){
            result = minmax(states[i], HUMAN);
            printf("score is for AI %d\n", states[i] -> score );
            states[i] -> score = result -> score;
        }else{
            result = minmax(states[i], AI);
            printf("score is for HUMAN %d\n", states[i] -> score );
            states[i] -> score = result -> score ;
        }
        
    }

    struct state * bestMove = (struct state *) malloc (sizeof(struct state));
    //if it is the AI's turn try and find the move with the highest score
    int **newBoard = NULL;
    if (player == AI){
        printf("AI\n");
        int bestScore = -1000;
        for(int i = 0; i < emptySpace; i++){
            if(states[i] -> score > bestScore){
                bestScore = states[i] -> score;
                bestMove -> player = gameState -> player;
                bestMove -> board = initBoard(newBoard);
                bestMove -> score = bestScore;
                deepIntCopy(bestMove -> board, gameBoard);
            }
        }
    //if its not the AI's turn then find the move with the lowest score
    }else{
        int bestScore = 1000;
        printf("HUMAN\n");
        for(int i =0; i < emptySpace; i ++){
            if (states[i] -> score < bestScore){

                bestScore = states[i] -> score;
                bestMove -> player = gameState -> player;

                bestMove -> board = initBoard(newBoard);
                bestMove -> score = bestScore;
                deepIntCopy(bestMove -> board, gameBoard);
                printf("yes\n");
            }
        }
    }
    printf("returning a move %d\n", bestMove -> score);
    free(boardSpaceCoords[0]);
    printf("returning after free");
    // free(boardSpaceCoords[1]);
    // printf("returning after free");
    free(boardSpaceCoords);
    printf("returning after free");
    return bestMove;


    
}
