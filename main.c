#include <stdio.h>
#include <stdlib.h>
#define EASY_BOARD_SIZE 6
#define Medium_BOARD_SIZE 9
#define Hard_BOARD_SIZE 12
char EASY_game_board[EASY_BOARD_SIZE][EASY_BOARD_SIZE];
char Medium_game_board[Medium_BOARD_SIZE][Medium_BOARD_SIZE];
char Hard_game_board[Hard_BOARD_SIZE][Hard_BOARD_SIZE];
void LEVEL_SELLECTION();
void Easy_board_building ();
void Medium_board_building ();
void Hard_board_building ();

int main()
{
    LEVEL_SELLECTION();

    return 0;
}
void LEVEL_SELLECTION()
{
    int x;
    printf("choose the level\n1)Easy\n2)Medium\n3)Hard\n");
    do{scanf("%d",&x);} while (x!=1 && x!=2 && x!=3);
        switch (x){
        case 1:
         Easy_board_building ();
          break;
        case 2:
           Medium_board_building ();
           break;
       case 3:
       Hard_board_building ();
       break;
        }
}
void Easy_board_building ()
{

   int i, j;
    int row, col;
    printf("Ready..steady..\nPLAY!\n\n");

    // Assign char 'o' for all board elements

    for(i = 0; i < EASY_BOARD_SIZE; i++)
        for(j = 0; j < EASY_BOARD_SIZE; j++)
             EASY_game_board[i][j] = 'o';


    // Print board

    for(col = 0; col < EASY_BOARD_SIZE; col++)
        printf("%d ", col + 1);

    printf("\n\n");

    for(row = 0; row < EASY_BOARD_SIZE; row++)
    {
        for(col = 0; col < EASY_BOARD_SIZE; col++)
        {
            printf("%c ",  EASY_game_board[row][col]);
        }
        printf(" %d ", row + 1);
        printf("\n");
    }
}
void Medium_board_building ()
{
    int i, j;
    int row, col;
   printf("Ready..steady..\nPLAY!\n\n");

    // Assign char 'o' for all board elements

    for(i = 0; i < Medium_BOARD_SIZE; i++)
        for(j = 0; j < Medium_BOARD_SIZE; j++)
             Medium_game_board[i][j] = 'o';

    // Print board

    for(col = 0; col < Medium_BOARD_SIZE; col++)
        printf("%d ", col + 1);

    printf("\n\n");

    for(row = 0; row < Medium_BOARD_SIZE; row++)
    {
        for(col = 0; col < Medium_BOARD_SIZE; col++)
        {
            printf("%c ",  Medium_game_board[row][col]);
        }
        printf(" %d ", row + 1);
        printf("\n");
    }
}
void Hard_board_building ()
{
    int i, j;
    int row, col;
    printf("Ready..steady..\nPLAY!\n\n");

    // Assign char 'o' for all board elements

    for(i = 0; i < Hard_BOARD_SIZE; i++)
        for(j = 0; j < Hard_BOARD_SIZE; j++)
             Hard_game_board[i][j] = 'o';


    // Print board

    for(col = 0; col < Hard_BOARD_SIZE; col++)
        printf("%d ", col + 1);

    printf("\n\n");

    for(row = 0; row < Hard_BOARD_SIZE; row++)
    {
        for(col = 0; col < Hard_BOARD_SIZE; col++)
        {
            printf("%c ",  Hard_game_board[row][col]);
        }
        printf(" %d ", row + 1);
        printf("\n");
    }
}
