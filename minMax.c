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
    if (gameFinished(gameState, HUMAN) == 1){
        gameState -> score = -1;
        return gameState;
    }else{
        if (gameFinished(gameState, AI) ==1){
            gameState -> score = 1;
            return gameState;
        }else{
            if (gameFinished(gameState, player) == 2){
                gameState -> score = 0;
                return gameState;
            }
        }
    }

    //for each space on the board that is empty, try placing a marker on it
    int result;
    int bestScore; 
    if (player == AI){
        bestScore = -1000;
    }else{
        if (player == HUMAN){
            bestScore = 1000;
        }
    }
    struct state *bestMove = (struct state *) malloc (sizeof(struct state));
    bestMove -> player = gameState -> player;
    int **newBoard = NULL;
    bestMove -> board = initBoard(newBoard);
    for ( i = 0; i < boardSize; i++){
        for (j =0; j<boardSize; j++){
            if (gameBoard[i][j] == 0){
                gameState -> board[i][j] = player;
                if (player == AI){
                    result = minmax(gameState, HUMAN) -> score;
                    if (result > bestScore){
                        bestMove -> score = result ;
                        bestScore = result ;
                        deepIntCopy(bestMove -> board, gameState -> board);
                        
                    }
                }else{
                    result = minmax(gameState, AI) -> score;
                    if (result < bestScore){
                        bestMove -> score = result ;
                        bestScore = result ;
                        deepIntCopy(bestMove -> board, gameState -> board);
                    }
                }
                gameState -> board[i][j] = 0;
            }
        }
    }
    return bestMove;


    
}
