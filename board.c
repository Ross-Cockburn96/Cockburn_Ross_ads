#include <stdlib.h>
#include <stdio.h>
#include "state.h"
#include "moveHistory.h"

#define TRUE 1
#define FALSE 0

void printBoard(int, struct state *);
void initialiseState(struct state **, int);
void start(struct state **, struct moveHistory **, int);
int gameFinished(struct state *, int);
int checkRows(struct state *, int);
int checkColumns(struct state *, int);
int checkDiagonals(struct state *, int);





char p1[3][25] = {" o o o ", " o   o ", " o o o "};
char p2[3][25] = {" x   x ", "   x   ", " x   x "};

int main(void)
{
    int size, i, j;
    struct state *game_state;
    struct moveHistory *history;
    history = NULL;

    printf("enter size of board\n");
    scanf("%d", &size);
    initialiseState(&game_state, size);
    printf("initialised\n");
    printf("initialised history\n");
    //system("cls");
    printBoard(size, game_state);

    
    start(&game_state, &history, size);
    return 0;
}

void start(struct state **game_state, struct moveHistory ** history, int size)
{
    int finished = FALSE;
    int x, y;
    int *square;
    while (finished == FALSE)
    {
        printf("player %d, enter your move, grid is %d by %d enter [row] [column]\n", (*game_state)->player, size, size);
        scanf("%d%d", &x, &y);
        
        square = &(*game_state) -> board[x-1][y-1];
        updateHistory (history, (*game_state));
        display((*history));
        if (*square == 0){
            *square = (*game_state) ->player;
            int moveEffect = gameFinished((*game_state), size);
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

            //switch player after turn is made
            if ((*game_state)->player == 1)
            {
                (*game_state)->player = 2;
            }
            else
            {
                (*game_state)->player = 1;
            }
            //system("cls");
            printBoard(size, (*game_state));
        }
        else
        {   

            printf("that square is occupied, choose another square\n");
        }
        
    }
}

int gameFinished(struct state *gameState, int size)
{
    if (checkRows(gameState, size) == TRUE)
    {
        return 1;
    }
    else
    {
        if (checkColumns(gameState, size) == TRUE)
        {
            return 1;
        }
        else
        {
            if (checkDiagonals(gameState, size) == TRUE)
            {
                return 1;
            }
            return 0;
        }
    }
}

int checkRows(struct state *gameState, int size)
{
    int i, j, marker, matchCount;
    int **ptr = (gameState->board);

    //loop checking matches on rows
    for (i = 0; i < size; i++)
    {
        marker = **(ptr + i); //this is the first marker on every row
        if (marker == 0)
        {
            continue; //if the first marker on the row is empty skip to the next row.
        }
        //printf("marker is %d\n", marker);
        matchCount = 0; //this will be equal to the size of the board if there is a winning row
        for (j = 0; j < size; j++)
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
            if (matchCount == size)
            {

                return TRUE; //this is a winning row
            }
        }
    }
    return FALSE;
}

int checkColumns(struct state *gameState, int size)
{
    int i, j, marker, matchCount;
    int **ptr = (gameState->board);

    //loop checking matches on columns
    for (i = 0; i < size; i++)
    {
        marker = *(*(ptr) + i); //this is the first marker on every column
        if (marker == 0)
        {
            continue; //if the first marker on the column is empty then skip to the next row
        }
        matchCount = 0;
        for (j = 0; j < size; j++)
        {
            if (*(*(ptr + j) + i) != marker)
            { //each element in the column
                break;
            }
            else
            {
                matchCount++;
            }
            if (matchCount == size)
            {
                return TRUE;
            }
        }
    }
    return FALSE;
}

int checkDiagonals(struct state *gameState, int size)
{
    int i, marker, matchCount;
    int **ptr = (gameState->board);
    marker = **(ptr); //marker is the top left marker on board
    if (marker != 0)
    {
        matchCount =0;
        for (i = 0; i < size; i++)
        {
            if (*(*(ptr + i) + i) != marker) //check the left -> right diagonal 
            {
                break;
            }
            else
            {
                matchCount++;
            }
            if (matchCount == size)
            {
                return TRUE;
            }
        }
    }
    marker = *(*(ptr)+size-1); //marker is top right marker on board
    if (marker != 0)
    {
        matchCount =0;
        for (i=0; i<size; i++)
        {
            if (*(*(ptr + i) +size-(i+1)) != marker) //check the right -> left diagonal 
            {
                break;
            }
            else
            {
                matchCount++;
            }
            if (matchCount == size)
            {
                return TRUE;
            }
        }
    }

    return FALSE;
    
}
//creates a visual board in the terminal based on the size input the user has given
void printBoard(int size, struct state *game_state)
{
    printf("\n\n");
    int i, boardCount = 0;
    char line[9] = "--------";
    for (i = 0; i < (size * 4) - 1; i++)
    { //i represents each row of output
        int j;
        if (i % 4 == 0 && i != 0)
        {
            boardCount++;
        }
        if (i % 4 == 3)
        {
            printf("-");
            for (j = 0; j < size; j++)
            { //j represents a column of output (column is 8 characters wide)
                printf("%s", line);
            }
            printf("\n");
        }
        else
        {
            for (j = 0; j < size - 1; j++)
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

void initialiseState(struct state **game_state, int boardSize)
{
    int i, j;
    *game_state = (struct state *)malloc(sizeof(game_state));
    (*game_state)->player = 1;
    (*game_state)->board = (int **)malloc(boardSize * sizeof(int **));
    for (i = 0; i < boardSize; i++)
    {
        (*game_state)->board[i] = (int *)malloc(boardSize * sizeof(int *));
    }
    for (i = 0; i < boardSize; i++)
    {
        for (j = 0; j < boardSize; j++)
        {
            (*game_state)->board[i][j] = 0;
        }
    }
}