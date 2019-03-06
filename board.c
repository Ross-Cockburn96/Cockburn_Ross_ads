#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

void setupBoard(int);
void initialiseState(struct state **, int);

struct state {
    int player;
    int **board;
    
};



int main(void){
    int size, i, j;
    struct state *game_state;
    printf("enter size of board\n");
    scanf("%d", &size);
    setupBoard(size);
    initialiseState(&game_state, size);

    for (i =0; i<size; i++){
        for (j=0; j<size; j++){
            printf("%d ", game_state -> board[i][j]);
        }
    }
    return 0;
}

//creates a visual board in the terminal based on the size input the user has given 
void setupBoard(int size){
    int i;
    char line[9] = "--------";
    for (i=1; i<size*4; i++){
        int j;
        if (i % 4 == 0){
            for (j=0; j<size; j++){
                printf("%s", line);
            }
            printf("\n");
        }else{
            for (j=0; j<size-1; j++){
                printf("\t|");
            }
            printf("\n");
        }
    }
}

void initialiseState(struct state **game_state, int boardSize){
    int i, j;
    *game_state = (struct state *) malloc (sizeof(game_state));
    (*game_state) -> player = 1;
    (*game_state) -> board = (int**) malloc(boardSize * sizeof(int *));
    for (i=0; i<boardSize; i++){
        (*game_state) -> board[i] = (int *) malloc(boardSize * sizeof(int *));
    }
    for (i =0; i<boardSize; i++){
        for (j=0; j<boardSize; j++){
            (*game_state) -> board[i][j] = 0;
        }
    }

    
}