#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

void setupBoard(int);



int main(void){
    int size;
    printf("enter size of board\n");
    scanf("%d", &size);
    setupBoard(size);
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