#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

void printBoard(int, struct state *);
void initialiseState(struct state **, int);
void start(struct state **, int);

struct state {
    int player;
    int **board;
    
};


char p1[3][25] = {" o o o ", " o   o ", " o o o "};
char p2[3][25] = {" x   x ", "   x   ", " x   x "};

int main(void){
    int size, i, j;
    struct state *game_state;
    
    printf("enter size of board\n");
    scanf("%d", &size);
    initialiseState(&game_state, size);
    printBoard(size, game_state);
    

    start(&game_state, size);
    return 0;
}

void start(struct state **game_state, int size){
    int finished = FALSE;
    int x,y;
    while (finished == FALSE){
        printf("player %d, enter your move, grid is %d by %d", (*game_state) -> player, size, size);
        scanf("%d%d", &x, &y);
        (*game_state) -> board[x-1][y-1] = (*game_state) -> player;
        if ((*game_state) -> player == 1){
            (*game_state) -> player = 2;
        }else{
            (*game_state) -> player = 1;
        }
        printBoard(size, (*game_state) );
        
    }
    printf ("coords are x: %d and y %d", x,y);
}

//creates a visual board in the terminal based on the size input the user has given 
void printBoard(int size, struct state *game_state){
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
    printf("\n\n----------------------------------------------------");
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