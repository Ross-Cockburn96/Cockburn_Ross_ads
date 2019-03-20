#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "state.h"
#include "moveHistory.h"
#include "board.h"

#define TRUE 1
#define FALSE 0







char p1[3][25] = {" o o o ", " o   o ", " o o o "};
char p2[3][25] = {" x   x ", "   x   ", " x   x "};
int boardSize;

int main(void)
{
    struct state *game_state;
    struct moveHistory *history;
    history = NULL;
    game_state = NULL;

    printf("enter size of board\n");
    scanf("%d", &boardSize);
    initialiseState(&game_state);
    initialiseHistory(&history);
    printf("initialised\n");

    printf("initialised history\n");
    //system("cls");
    printBoard(game_state);


    start(&game_state, &history );
    printf("end of game");
    return 0;
}
//change this so we aren't passing states around, only the history and we access the state from the history structure
void start(struct state **game_state, struct moveHistory ** history)
{
    int finished = FALSE;
    int x, y;
    int *square;
    char ans[1];
    while (finished == FALSE)
    {
        printf("player %d, enter your move, grid is %d by %d enter [row] [column]\n", (*game_state)->player, boardSize, boardSize);
        scanf("%d%d", &x, &y);

        square = &((*game_state) -> board[x-1][y-1]);

        if (*square == 0){
            *history = validateHistory(history);
            // for (int i = 0; i < 3; i++){
            //     for (int j = 0; j < 3; j ++){
            //         printf("old board is %d\n", (*game_state)->board[i][j]);
            //     }
            // }

            *square = (*game_state) ->player; //change value of board to whatever player's shot it is
            int moveEffect = gameFinished((*game_state));
            if (moveEffect == 1)
            {
                printf("player %d wins\n", (*game_state)->player);
                finished = TRUE;
                break;
            }
            if (moveEffect == 2)
            {
                printf("draw\n");
                break;
            }
            //mark who's turn it is next 
            if ((*game_state)->player == 1)
            {
                (*game_state)->player = 2;
            }
            else
            {
                (*game_state)->player = 1;
            }
            updateHistory (history, (*game_state)); //updates history with the current state before changing the state with user's turn

            
            //system("cls");
            printBoard((*game_state));
            printf ("Would you like to enter rewind mode?\n y/n ");
            scanf ("%s", ans);
            if (strcmp(ans, "y") ==0){
                rewindState(game_state, history);
            }
            

        }
        else
        {

            printf("that square is occupied, choose another square\n");
        }

    }
    printf("FINISHED");
}

void rewindState(struct state **game_state, struct moveHistory **move_history)
{
    char c[3];
    int finished = FALSE;
    while (finished == FALSE){
        printf ("Enter R to redo, U to undo a move and F to finish");
        scanf ("%s", c);
        if (strcmp(c, "U") ==0){
            undo(game_state, move_history);
            printf("player is now %d\n", (*game_state) -> player);
            printBoard((*game_state));
        }
        if (strcmp(c, "F") ==0){
            finished = TRUE;
        }
    }

}

void undo(struct state **game_state, struct moveHistory **move_history){
    struct state *prevState;
    prevState = (*move_history) -> prev -> current_state;
    *move_history = (*move_history) -> prev;
    deepIntCopy((*game_state) -> board, prevState -> board);
    (*game_state) -> player = prevState -> player;


}
int gameFinished(struct state *gameState)
{
    if (checkRows(gameState ) == TRUE)
    {
        return 1;
    }
    else
    {
        if (checkColumns(gameState ) == TRUE)
        {
            return 1;
        }
        else
        {
            if (checkDiagonals(gameState ) == TRUE)
            {
                return 1;
            }
            return 0;
        }
    }
}

int checkRows(struct state *gameState)
{
    int i, j, marker, matchCount;
    int **ptr = (gameState->board);

    //loop checking matches on rows
    for (i = 0; i < boardSize; i++)
    {
        marker = **(ptr + i); //this is the first marker on every row
        if (marker == 0)
        {
            continue; //if the first marker on the row is empty skip to the next row.
        }
        //printf("marker is %d\n", marker);
        matchCount = 0; //this will be equal to the size of the board if there is a winning row
        for (j = 0; j < boardSize; j++)
        {
            if (*(*(ptr + i) + j) != marker)
            { //this is each element in the row
                //printf("%d is not = to marker\n" ,*(*(ptr + i)+j) );
                break; //if one of the elements is not equal to the marker then there is no point checking the rest in this row
            }
            else
            {
                //printf("value %d is = to marker\n", *(*(ptr+i)+j));
                matchCount++;
                //printf("%d is number of matches\n", matchCount);
            }
            if (matchCount == boardSize)
            {

                return TRUE; //this is a winning row
            }
        }
    }
    return FALSE;
}

int checkColumns(struct state *gameState)
{
    int i, j, marker, matchCount;
    int **ptr = (gameState->board);

    //loop checking matches on columns
    for (i = 0; i < boardSize; i++)
    {
        marker = *(*(ptr) + i); //this is the first marker on every column
        if (marker == 0)
        {
            continue; //if the first marker on the column is empty then skip to the next row
        }
        matchCount = 0;
        for (j = 0; j < boardSize; j++)
        {
            if (*(*(ptr + j) + i) != marker)
            { //each element in the column
                break;
            }
            else
            {
                matchCount++;
            }
            if (matchCount == boardSize)
            {
                return TRUE;
            }
        }
    }
    return FALSE;
}

int checkDiagonals(struct state *gameState)
{
    int i, marker, matchCount;
    int **ptr = (gameState->board);
    marker = **(ptr); //marker is the top left marker on board
    if (marker != 0)
    {
        matchCount =0;
        for (i = 0; i < boardSize; i++)
        {
            if (*(*(ptr + i) + i) != marker) //check the left -> right diagonal
            {
                break;
            }
            else
            {
                matchCount++;
            }
            if (matchCount == boardSize)
            {
                return TRUE;
            }
        }
    }
    marker = *(*(ptr)+boardSize-1); //marker is top right marker on board
    if (marker != 0)
    {
        matchCount =0;
        for (i=0; i<boardSize; i++)
        {
            if (*(*(ptr + i) +boardSize-(i+1)) != marker) //check the right -> left diagonal
            {
                break;
            }
            else
            {
                matchCount++;
            }
            if (matchCount == boardSize)
            {
                return TRUE;
            }
        }
    }

    return FALSE;

}
//creates a visual board in the terminal based on the size input the user has given
void printBoard(struct state *game_state)
{
    printf("\n\n");
    int i, boardCount = 0;
    char line[9] = "--------";
    for (i = 0; i < (boardSize * 4) - 1; i++)
    { //i represents each row of output
        int j;
        if (i % 4 == 0 && i != 0)
        {
            boardCount++;
        }
        if (i % 4 == 3)
        {
            printf("-");
            for (j = 0; j < boardSize; j++)
            { //j represents a column of output (column is 8 characters wide)
                printf("%s", line);
            }
            printf("\n");
        }
        else
        {
            for (j = 0; j < boardSize - 1; j++)
            {
                if (game_state->board[boardCount][j] == 0)
                {
                    printf("\t|");
                }
                if (game_state->board[boardCount][j] == 1)
                {
                    printf("%s|", p1[i % 4]);
                }
                if (game_state->board[boardCount][j] == 2)
                {
                    printf("%s|", p2[i % 4]);
                }
            }
            if (game_state->board[boardCount][j] == 1)
            {
                printf("%s", p1[i % 4]);
            }
            if (game_state->board[boardCount][j] == 2)
            {
                printf("%s", p2[i % 4]);
            }
            printf("\n");
        }
    }
    printf("\n\n----------------------------------------------------\n");
}

void initialiseState(struct state **game_state)
{
    *game_state = (struct state *)malloc(sizeof(game_state));
    (*game_state)->player = 1;
    (*game_state)->board = initBoard((*game_state) -> board);
}

int **initBoard (int **board){
    int i,j;
    board = (int **) malloc(boardSize * sizeof(int *));
    for (i = 0; i < boardSize; i++)
    {
        board[i] = (int *) malloc (boardSize * sizeof(int));
        for (j=0; j< boardSize; j++){
            board[i][j] = 0;
        }
    }
   return board;
}

//function to free the allocated space of a game board
void freeBoard(int **board){
    int i;
    for (i = 0; i < boardSize; i++){
        free(board[i]);
    }
    free (board);
}

void deepIntCopy(int **newBoard, int **oldBoard){
    int i,j;
     for (i = 0; i < boardSize; i++){
        for (j = 0; j < boardSize; j ++){
            newBoard[i][j] = oldBoard[i][j];
        }
    }
}
