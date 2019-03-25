#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "state.h"
#include "moveHistory.h"
#include "board.h"
#include "minMax.h"

#define TRUE 1
#define FALSE 0


char p1[3][25] = {" o o o ", " o   o ", " o o o "};
char p2[3][25] = {" x   x ", "   x   ", " x   x "};
int boardSize;
int player1Score = 0;
int player2Score = 0;
int main(void)
{
    struct state *game_state;
    struct moveHistory *history;
    struct moveHistory **gameHistory;
    srand(time(NULL));
    gameHistory = (struct moveHistory **) malloc(sizeof(struct moveHistory*));
    int games = 0;
    char response[2] = "";
    int aiOpponent = 0;
    history = NULL;
    game_state = NULL;

    printf("enter size of board\n");
    scanf("%d", &boardSize);

    printf("do you want to play against AI?(y/n)");
    scanf("%s", response );
    if (strcmp(response, "y") ==0){
        aiOpponent = 1;
    }

    initialiseState(&game_state);
    initialiseHistory(&history);
    system("cls");
    printf("Player 1 - %d : %d - Player 2", player1Score, player2Score);
    printBoard(game_state);
    start(&game_state, &history, aiOpponent );
    printf("end of game\n");
    while (strcmp(response, "q") != 0){
        gameHistory[games] = (struct moveHistory *)malloc (sizeof(struct moveHistory));
        gameHistory[games] = &(*history);
        printf("play again?(y/n) or q to quit\n");
        scanf("%s", response);

        if (strcmp(response, "y") == 0){
            //delete the game board and create a new one
            freeBoard(game_state -> board);
            int **newBoard = NULL;
            game_state -> board = initBoard(newBoard);
            game_state -> player = 1;
            //don't free history space as it is being used by the gameHistory for game replaying 
            history = NULL;
            initialiseHistory(&history);
            system("cls");
            printf("Player 1 - %d : %d - Player 2", player1Score, player2Score);
            printBoard(game_state);
            start(&game_state, &history, aiOpponent);
            games++;
        }else{
            if (strcmp(response, "n") == 0){
                char resp[2] = "";
                while (strcmp(resp, "n")!=0){
                    printf("do you want to replay a previous game?(y/n)\n");
                    scanf("%s", resp);
                    if (strcmp(resp, "y") == 0){
                        int gameNum = 0;
                        printf("enter the number of the game you want to replay\n");
                        for (int i = 0; i <= games; i++){
                            printf("game %d\n", i+1);
                        }
                    scanf("%d", &gameNum);
                    gameNum --;
                    replayHistory(gameHistory[gameNum]);
                    }
                }
               
            }
        }
        
    }
    return 0;
}

void replayHistory(struct moveHistory *gameHistory){
    while (gameHistory -> prev != NULL){
        gameHistory = gameHistory -> prev;
    }
    while (gameHistory -> next != NULL){
        Sleep(1000);
        system("cls");
        printf("Player 1 - %d : %d - Player 2", player1Score, player2Score);
        printBoard(gameHistory -> current_state);
        gameHistory = gameHistory -> next;
        
    }
    Sleep(1000);
    system("cls");
    printf("Player 1 - %d : %d - Player 2", player1Score, player2Score);
    printBoard(gameHistory -> current_state);
    
}

void start(struct state **game_state, struct moveHistory ** history, int aiOpponent)
{
    int finished = FALSE;
    int x, y;
    int *square;
    char ans[2];
    while (finished == FALSE)
    {
        if (((*game_state) -> player ==2) && (aiOpponent == 1) && (boardSize <= 3)){
            *game_state = minmax((*game_state), (*game_state)->player);
        }else{
            if (((*game_state) -> player == 2) && (aiOpponent == 1) && (boardSize > 3)){
                int validMove = 0;
                while (validMove == 0){
                    int row = rand() % boardSize;
                    int column = rand() % boardSize;
                    if ((*game_state) -> board[row][column] == 0){
                        (*game_state) -> board[row][column] = (*game_state) -> player;
                        validMove = 1;
                    }
                }
            }else{

                printf("player %d, enter your move, grid is %d by %d enter [row] [column]\n", (*game_state)->player, boardSize, boardSize);
                scanf("%d%d", &x, &y);
            
                square = &((*game_state) -> board[x-1][y-1]);
                if (*square == 0){
                    *history = validateHistory(history);
                    *square = (*game_state) ->player; //change value of board to whatever player's shot it is
                }
                else
                {

                    printf("that square is occupied, choose another square\n");
                    continue;
                }
            }
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
        int moveEffect = gameFinished((*game_state), (*history)->prev->current_state->player);
        if (moveEffect == 1)
        {
            system("cls");
            printf("player %d wins\n", (*history)->prev->current_state->player);
            if ((*history) -> prev -> current_state -> player == 1){
                player1Score++;
            }else{
                player2Score++;
            }
            finished = TRUE;
            printf("Player 1 - %d : %d - Player 2", player1Score, player2Score);
            printBoard((*game_state));
            break;
        }
        if (moveEffect == 2)
        {   
            system("cls");
            printf("draw\n");
            finished = TRUE;
            printf("Player 1 - %d : %d - Player 2", player1Score, player2Score);
            printBoard((*game_state));
            break;
        }
        
        system("cls");
        printf("Player 1 - %d : %d - Player 2", player1Score, player2Score);
        printBoard((*game_state));
        printf ("Would you like to enter rewind mode?\n y/n ");
        scanf ("%s", ans);
        if (strcmp(ans, "y") ==0){
            rewindState(game_state, history);
        }
    }

    printf("FINISHED\n");
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
            system("cls");
            printf("Player 1 - %d : %d - Player 2", player1Score, player2Score);
            printBoard((*game_state));
        }
        if (strcmp(c, "R") == 0){
            redo(game_state, move_history);
            printf("player is now %d\n", (*game_state) -> player);
            system("cls");
            printf("Player 1 - %d : %d - Player 2", player1Score, player2Score);
            printBoard((*game_state));
        }
        if (strcmp(c, "F") ==0){
            finished = TRUE;
        }
    }

}

void undo(struct state **game_state, struct moveHistory **move_history){
    struct state *prevState;
    if ((*move_history) -> prev != NULL){
        prevState = (*move_history) -> prev -> current_state;
        *move_history = (*move_history) -> prev;
        deepIntCopy((*game_state) -> board, prevState -> board);
        (*game_state) -> player = prevState -> player;
    }else{
        printf("NO MOVES TO UNDO\n");
    }
    
}

void redo(struct state **game_state, struct moveHistory **move_history){
    struct state *nextState;
    if ((*move_history) -> next != NULL){
        nextState = (*move_history) -> next -> current_state;
        *move_history = (*move_history) -> next;
        deepIntCopy((*game_state) -> board, nextState -> board);
        (*game_state) -> player = nextState -> player;
    }else{
        printf("NO MOVES TO REDO\n");
    }
    
}
int gameFinished(struct state *gameState, int player)
{
    if (checkRows(gameState, player ) == TRUE)
    {
        return 1;
    }
    else
    {
        if (checkColumns(gameState, player ) == TRUE)
        {
            return 1;
        }
        else
        {
            if (checkDiagonals(gameState, player ) == TRUE)
            {
                return 1;
            }
            return 0;
        }
    }
}

int checkRows(struct state *gameState, int player)
{
    int i, j, marker, matchCount;
    int **ptr = (gameState->board);

    //loop checking matches on rows
    for (i = 0; i < boardSize; i++)
    {
        marker = **(ptr + i); //this is the first marker on every row
        if (marker == 0 || marker != player)
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

int checkColumns(struct state *gameState, int player)
{
    int i, j, marker, matchCount;
    int **ptr = (gameState->board);

    //loop checking matches on columns
    for (i = 0; i < boardSize; i++)
    {
        marker = *(*(ptr) + i); //this is the first marker on every column
        if (marker == 0 || marker != player)
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

int checkDiagonals(struct state *gameState, int player)
{
    int i, marker, matchCount;
    int **ptr = (gameState->board);
    marker = **(ptr); //marker is the top left marker on board
    if (marker != 0 && marker == player)
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
    if (marker != 0 && marker == player)
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
    if (board != NULL){
         free (board);
    }
   
}

void deepIntCopy(int **newBoard, int **oldBoard){
    int i,j;
     for (i = 0; i < boardSize; i++){
        for (j = 0; j < boardSize; j ++){
            newBoard[i][j] = oldBoard[i][j];
        }
    }
}

void printGameBoard(int ** board){
    for (int i = 0; i < boardSize; i ++){
        for (int j = 0; j < boardSize; j ++){
            printf("%d", board[i][j]);
        }
    }
}
