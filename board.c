#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

void printBoard(int, char p1[3][25], char p2[3][25], struct state *);
void initialiseState(struct state **, int);
void start(struct state **);

struct state {
    int player;
    int **board;
    
};




int main(void){
    int size, i, j;
    struct state *game_state;
    char p1[3][25] = {" o o o ", " o   o ", " o o o "};
    char p2[3][25] = {" x   x ", "   x   ", " x   x "};
    printf("enter size of board\n");
    scanf("%d", &size);
    initialiseState(&game_state, size);
    game_state -> board[1][1] = 2;
    printBoard(size, p1, p2,  game_state);
    

    //start(&game_state);
    return 0;
}

void start(struct state **game_state){
    int finished = FALSE;
    while (finished == FALSE){

    }
}

//creates a visual board in the terminal based on the size input the user has given 
void printBoard(int size, char p1[3][25],  char p2[3][25], struct state *game_state){
    int i, boardCount =0;
    char line[9] = "--------";
    for (i=0; i<(size*4) - 1 ; i++){ //i represents each row of output
        int j;
        if (i % 4 == 0 && i != 0 ){
            boardCount++;
        }
        if (i % 4 == 3 ){
            for (j=0; j<size; j++){ //j represents a column of output (column is 8 characters wide)
                printf("%s", line);
            }
            printf("\n");
        }else{
            for (j=0; j<size-1; j++){
                if (game_state -> board[boardCount][j] == 0){
                    printf("\t|");
                }
                if (game_state -> board[boardCount][j] == 1){
                    printf("%s|", p1[i % 4] );
                }
                if (game_state -> board[boardCount][j] == 2){
                    printf("%s|", p2[i % 4]);
                }
            }
            if(game_state -> board[boardCount][j] == 1){
                printf("%s", p1[i %4]);
            }
            if (game_state -> board[boardCount][j] == 2){
                printf("%s", p2[i % 4]);
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
            (*game_state) -> board[i][j] = 1;
        }
    }

    
}