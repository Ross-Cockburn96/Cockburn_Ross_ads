#include <stdlib.h>
#include <stdio.h>
#include "state.h"
#include "board.h"
#include "minMax.h"
#include <windows.h>

#define HUMAN 1
#define AI 2
extern int boardSize;
int count = 0;
struct state * minmax(struct state *gameState, int player){
    count++;
    int i,j;
    int **gameBoard = gameState -> board;
    int emptySpace = 0;
    int **boardSpaceCoords = (int**) malloc(boardSize * boardSize *sizeof(int*));
    for (i = 0; i < boardSize*boardSize; i++){
        boardSpaceCoords[i] = (int*) malloc (2 * sizeof(int));
    }

    int **temp;
    for ( i=0; i<boardSize; i++){
        for ( j=0; j<boardSize; j++){
            if (gameBoard[i][j] == 0){
        
                boardSpaceCoords[emptySpace][0] = i+1;
                boardSpaceCoords[emptySpace][1] = j+1;
                emptySpace++;
            }
        }
    }


    if (gameFinished(gameState, HUMAN) == 1){
        gameState -> score = -1;
        return gameState;
    }else{
        if (gameFinished(gameState, AI) ==1){
            gameState -> score = 1;
            return gameState;
        }else{
            if (emptySpace == 0){
                gameState -> score = 0;
                return gameState;
            }
        }
    }

    int scores[9];
    //for each space on the board that is empty, try placing a marker on it
    struct state * result = (struct state *) malloc (sizeof(struct state));
    int bestScore; 
    if (player == AI){
        bestScore = -1000;
    }else{
        if (player == HUMAN){
            bestScore = 1000;
        }
    }
    struct state * bestMove = (struct state *) malloc (sizeof(struct state));
    bestMove -> player = gameState -> player;
    int **newBoard = NULL;
    bestMove -> board = initBoard(newBoard);
    for ( i = 1; i <= emptySpace; i++){
        int row = boardSpaceCoords[i-1][0];
        int column = boardSpaceCoords[i-1][1];

        gameState -> board[row-1][column-1] = player;

        if (player == AI){
            result = minmax(gameState, HUMAN);
            if (result -> score > bestScore){
                bestMove -> score = result -> score;
                bestScore = result -> score;
                deepIntCopy(bestMove -> board, gameState -> board);
            }
        }else{
            result = minmax(gameState, AI);
            if (result -> score < bestScore){
                bestMove -> score = result -> score;
                bestScore = result -> score;
                deepIntCopy(bestMove -> board, gameState -> board);
            }
        }
        gameState -> board[row-1][column-1] = 0;
        
    }
   
    return bestMove;


    
}
