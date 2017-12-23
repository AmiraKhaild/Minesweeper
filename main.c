#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>

int row;
int column;
char **board;
char **my_data;
clock_t my_time,start_t,end_t;
int moves=0;
int mines;
int flags=0;
long scorearray[10];
char HighScoreNames[10][30];
int scoresize;
int read_high_score();
void write_in_file();
void sorting_the_scores ();
void print_high_score();

void save_game(){
FILE *f;
int i,j;
char name[50];
char filename[50];
char x[100];
printf("Please enter your name:");
fflush(stdin);
scanf("%[^\n]",name);
strcat(name,".txt");
for(i=0;i<strlen(name)-1;i++)
    if(name[i]==' ')
        name[i]='_';
f=fopen(name,"w");
//printf("check r");
if(f==NULL){
    printf("File couldn't be created!\n");
    exit(0);
}
//printf("check t");
fprintf(f,"%d\t%d\n",row,column);
for(i=0;i<row;i++){
    for(j=0;j<column;j++){
    fprintf(f,"%c ",my_data[i][j]);
    }fprintf(f,"\n");
}
fprintf(f,"\n");
for(i=0;i<row;i++){
    for(j=0;j<column;j++){
    fprintf(f,"%c ",board[i][j]);
    }fprintf(f,"\n");
}
//printf("chek y");

fclose(f);
printf("Game saved successfully!\nBye!!\n");
char c;
printf("Enter any key to return to main menu\n");
fflush(stdin);
scanf("%c",&c);
main_menu();
}

void load_game()
{
FILE *f;
int i,j;
char name[50];
char x[100];
printf("Please enter your name:");
fflush(stdin);
scanf("%[^\n]",name);
strcat(name,".txt");
for(i=0;i<strlen(name)-1;i++)
    if(name[i]==' ')
        name[i]='_';
f=fopen(name,"r");
//printf("check r");
if(f==NULL){
    printf("File couldn't be created!\n");
    exit(0);
}
fscanf(f,"%d\t%d\n",&row,&column);
board=(char**)malloc(row*sizeof(char*));
    my_data=(char**)malloc(row*sizeof(char*));
    for(i=0;i<row;i++)
    {
        board[i]=(char*)malloc(column*sizeof(char));
        my_data[i]=(char*)malloc(column*sizeof(char));
    }
for(i=0;i<row;i++){
   //printf("enter 1");
    for(j=0;j<column;j++){
     //       printf("%d and %d\n",i,j);
    fscanf(f,"%c ",&my_data[i][j]);
    }fscanf(f,"\n");
}
//printf("check t");
fscanf(f,"\n");
for(i=0;i<row;i++){
    for(j=0;j<column;j++){
    fscanf(f,"%c ",&board[i][j]);
    }fscanf(f,"\n");
}
    fclose(f);
    display_board(2);

}


void flag()
{
    int r,c;
    printf("Enter the coordinates of the cell to flag:(enter -1 at any point to return to move choice menu) \n");
    printf("Row:");
    scanf("%d",&r);
    if(r==-1)
        director(2);
    printf("Column:");
    scanf("%d",&c);
    if(c==-1)
        director(2);
    if(board[r-1][c-1]=='0')
        printf("(((You can't flag an open cell!!)))\n");
    else{
        board[r-1][c-1]='F';
        moves++;
        flags++;}
    //printf("%c",board[r-1][c-1]);
    int x;
    printf("go to chwin\n\n");
    x=check_win();
    printf("bacl from chwin\n\n");
    display_board(2);
}

void question()
{
    int r,c;
    printf("Enter the coordinates of the cell to question:(enter -1 at any point to return to move choice menu) \n");
    printf("Row:");
    scanf("%d",&r);
    if(r==-1)
        director(2);
    printf("Column:");
    scanf("%d",&c);
    if(c==-1)
        director(2);
    if(board[r-1][c-1]=='0')
        printf("(((You can't question an open cell!!)))\n");
    else{
        board[r-1][c-1]='?';
        moves++;}
    //printf("%c",board[r-1][c-1]);
    display_board(2);
}

void unmark()
{
    int r,c;
    printf("Enter the coordinates of the cell to unmark:(enter -1 at any point to return to move choice menu) \n");
    printf("Row:");
    scanf("%d",&r);
    if(r==-1)
        director(2);
    printf("Column:");
    scanf("%d",&c);
    if(c==-1)
        director(2);
    if(board[r-1][c-1]=='F' || board[r-1][c-1]=='?'){
        board[r-1][c-1]='X';
        moves++;}
    else
        printf("Can't unmark a cell that doesn't contain a flag or question!!");
    display_board(2);
}
void my_exit(int way)
{
    if(way==1){
    printf("Do you wish to save the game and continue it later?(y/n)\n");
    char c;
    fflush(stdin);
    scanf("%c",&c);
    if(c=='Y' || c=='y'){
        save_game();}
    else if(c=='n' || c=='N'){
        printf("Thanks for Playing!!\n");
    }
    }
        printf("Thanks for Playing!!\n");
        free(board);
        free(my_data);
        exit(2);}

void director(int way)
{
    printf("\n\nPlease choose your next move:\n1)Open\n2)Flag\n3)Question\n4)Unmark\n5)Stop the game\n");
    char x;
    fflush(stdin);
    scanf("%c",&x);
    switch (x)
    {
    case '1':
        open_cell();
        break;
    case '2':
        flag();
        break;
    case '3':
        question();
        break;
    case '4':
        unmark();
        break;
    case '5':
        my_exit(1);
        break;
    }
}
int my_isdigit(char c)
{
        //printf(" c is %c\n\n",c);
        if(c=='1' || c=='2' || c=='3' || c=='4' || c=='5' || c=='6' || c=='7' || c=='8' || c=='9')
        return 0;
    else
        return -1;
}
void open_adjacent_empty(int r,int c)
{
    int i,j;
    int allow=1;
    int flagcount=0;
    int x;
    int ac1,ar1,ac2,ar2;
    ac1=c;
    ar1=r;
    ac2=c;
    ar2=r;
    i=r-1;
    j=c-1;
    if(i<0)
        ar1=1;
    if(j<0)
        ac1=1;
    if(r+1>row)
        ar2=row-1;
    if(c+1>column)
        ac2=column-1;
        int isnum;
        isnum=my_isdigit(board[r][c]);
        //printf("\nisnum is %d\n",isnum);
        if(isnum==0)
        {
        for(i=ar1-1;i<ar2+2;i++)
        {

            if(i>row-1){
                break;}
                //printf("check 1");

        for(j=ac1-1;j<ac2+2;j++)
        {

            if(j>column)
                break;
                //printf("check 2");
                if(board[i][j]=='F')
                    flagcount++;
                   // printf("check 3");
        }
        }
        int flagnum;
        //printf("check 4");
        char num=board[r][c];
        flagnum=atoi(&num);
        printf("flagnum is %d\n",flagnum);
        printf("flagcount is %d\n",flagcount);
        if(flagcount>flagnum){
            printf("You flagged adjacent cells more than the actual adjacent mines!!\n");
            director(2);}
        if(flagcount<flagnum){
            //4printf("Please flag %c adjacent cells you suspect contain mines to open the adjacent supposed empty cells!\n");
            display_board(2);
            director(2);}
        }
//printf(" %d and %d and %d and %d\n",r,ar1,ar2,row-1);
//printf(" %d and %d and %d and %d\n",c,ac1,ac2,column-1);
    for(i=ar1-1;i<ar2+2;i++)
        {
                    //printf("%d and %d\n",i,row);

            if(i>row-1){
                break;}
                        //printf("broke here3\n");

        for(j=ac1-1;j<ac2+2;j++)
        {
                   // printf("broke here4\n");

            if(j>column)
                break;
                //printf("broke here 5\n");
         //printf("%d and %d",i,j);
         //printf("%d\n\n",(board[i][j]!='*' && board[i][j]!='F' && board[i][j]!=' '));
         //printf("Row %d and Column %d is %c\n",i+1,j+1,board[i][j]);
               //    printf("%d and %d\n",i,j);   printf("are %c\n\n",board[i][j]);
            //printf("x is %d\n",x);
            if(my_data[i][j]=='*'&&board[i][j]!='F')
                game_over(i,j);
            if(board[i][j]!='F' && board[i][j]!=my_data[i][j])
            {
           //     printf("check 1\n");
           //printf("was %c\t",board[i][j]);
                board[i][j]=my_data[i][j];
             //   printf("became %c\n",board[i][j]);
             //printf("check 2\n");
             //printf("%d and %d\n",i,j);
            //
             //printf("are %c\n\n",board[i][j]);
             x=my_isdigit(board[i][j]);
             //printf("%d\n",x);
             if(x!=0){
                open_adjacent_empty(i,j);
             }
                //printf("chech hete\n");
            }

        }
        //printf("done row %d\n",i+1);
        //printf("broke here1\n");

}
//printf("check alpha\n");
}

void game_over(int r,int c)
{
    int i,j;
    for(i=0;i<row;i++)
    {
        for(j=0;j<column;j++)
        {
            if(my_data[i][j]=='*')
                board[i][j]='M';
                if(my_data[i][j]=='*'&&board[i][j]=='F')
                    board[i][j]='*';
                if(board[i][j]=='F'&&my_data[i][j]!='*')
                    board[i][j]='-';

        }
        printf("done with loop\n");
    }
    board[r][c]='!';
    display_board(1);
    printf("Game Over !!");
    char c2;
    printf("\nEnter any key to exit the game\nEter 'M' to return to main menu\n");
    fflush(stdin);
    scanf("%c",&c2);
    if(c2=='M' || c2=='m')
        main_menu();
        else
        my_exit(2);
}
void get_size(){
    fflush(stdin);
    printf("Please enter the number of rows:\n ");
    scanf("%d",&row);
    printf("Please enter the number of columns: \n");
    scanf("%d",&column);
}

void create_board(){
    int i,j;
    for(i=0;i<row;i++)
    {
        for(j=0;j<column;j++){
            board[i][j]='X';
            my_data[i][j]='0';
         //   printf("is %c\n",my_data[i][j]);
        }
    }
}

void display_board(int way){
    int i,j;
    system("cls");
    printf("  |");
    for(j=0;j<column;j++)
    {
        printf(" %d |",j+1);
    }
    printf("\n");
    for(i=0;i<row;i++)
    {
        printf("%02d|",i+1);
        for(j=0;j<column;j++)
        {

            if(board[i][j]=='0')
                printf("   |");
                else
                    printf(" %c |",board[i][j]);
            }
            printf("%d\n",i+1);
            }
            printf("\n");
            if(way==2)
            {
                director(2);}
}

void mines_func(int r,int c){
    srand(time(0));
    int x,y,i,j;
    mines= 1+ (row*column)/10;
    //printf("check 5");
    for(i=0;i<mines;i++)
    {
        //printf("check 5.5");
        do{
        x=rand()%row;
        y=rand()%column;
        }while(x==r || y==c);
        //printf("%d and %d",x,y);
        my_data[x][y]='*';
    //printf("check 6\n");
    }
//printf("check 7");
}

void init_board()
{
    int i,j,k,l;
    for(i=0;i<row;i++)
    {

        for(j=0;j<column;j++)
        {
            for(k=i-1;k<i+2&& k<row;k++)
            {

                if(k<0)
                k=0;
            for(l=j-1;l<j+2 && l<column;l++)
        {

            if(l<0)
                l=0;
            if(my_data[k][l]=='*'&& !(l==j && k==i) && my_data[i][j]!='*')
                //my_data[i][j]='0';
                my_data[i][j]++;
        }

            }
    }
    }
}
void start_new_game(){
    int i;
    get_size();
    board=(char**)malloc(row*sizeof(char*));
    my_data=(char**)malloc(row*sizeof(char*));
    for(i=0;i<row;i++)
    {
        board[i]=(char*)malloc(column*sizeof(char));
        my_data[i]=(char*)malloc(column*sizeof(char));
    }
    create_board();
    display_board(1);
    open_cell(1);

}

void create_win_board()
{
    int i,j;
    for(i=0;i<row;i++)
    {
        for(j=0;j<column;j++)
        {
            if(my_data[i][j]=='*')
                board[i][j]='F';
                if(board[i][j]=='X')
                    board[i][j]=my_data[i][j];
        }
    }

}

void write_in_file()
{FILE *f1;
    int i;
    f1=fopen("highscore.txt","w");
    if (f1==NULL)

    { printf("not found!");
    exit(1); }

        for (i=scoresize;i>0; i-- )
        {
            fprintf(f1,"%s,%d\n",HighScoreNames[i-1],scorearray[i-1]);

}}
void sorting_the_scores()
{ int i,j,temp;
 char temp1[50];
        for (i = 0; i < scoresize; i++)// bubble sorting in ascending order
{
        for (j = 0; j < (scoresize - i - 1); j++)
        {

            if (scorearray[j] > scorearray[j + 1])

            {

                temp = scorearray[j];
                strcpy(temp1,HighScoreNames[j]);
                scorearray[j] = scorearray[j + 1];
                 strcpy(HighScoreNames[j],HighScoreNames[j+1]);
               scorearray[j + 1] = temp;
                strcpy(HighScoreNames[j+1],temp1);
            }



        }

    }}


int check_win()
{
    int i,j,win=1;
    printf("mines is %d and flags is %d\n\n\n",mines,flags);
    if(mines==flags)
    {
    for(i=0;i<row;i++)
        for(j=0;j<column;j++)
    {
        if(board[i][j]=='F')
        {
            if(my_data[i][j]!='*'){
                    printf("didn't win bec. %c and %c\n",board[i][j],my_data[i][j]);
                win=0;
                break;}
        }
    }
    }
    if(flags!=mines){
    for(i=0;i<row;i++)
    {
        for(j=0;j<column;j++)
    {
        if (board[i][j]=='X')
        {
            if(my_data[i][j]!='*')
            {
            win=0;
            break;
            }
        }
    }
    }
    }
    if(win==1)
    {
        create_win_board();
        display_board(1);
        printf("\nCongratulations!!\nYou Won!\n");
        after_win();
            }
}
void after_win()
{
    long score;
    end_t=clock();
    double time;
    time=(double)(end_t-start_t)/1000;
    if(time<1)
        time=1.0;
    //printf("%f and %d\n",time,moves);
    score=((pow(row,4))*(pow(column,4)))/(int)(time*moves);
        printf("Score=%ld\n\n",score);
        printf("Enter your name to save you score: \n");
        fflush(stdin);
        scanf("%[^\n]",HighScoreNames[scoresize]);
        scorearray[scoresize]=score;
        scoresize++;
         sorting_the_scores();
    write_in_file();
    char c;
    printf("\nEnter any key to display high scores\nEnter 'M' to return to main menu without displaying high scores");
    fflush(stdin);
    scanf("%c",&c);
    if(c=='M' || c=='m')
        main_menu();
    else
        print_high_score();
        exit(0);
}
void open_cell(int way){
    int r,c;
    printf("Enter the coordinates of the cell to open:(enter -1 at any point to return to move choice menu) \n");
    printf("Row:");
    scanf("%d",&r);
    if(r==-1)
        director(2);
    printf("Column:");
    scanf("%d",&c);
    if(c==-1)
        director(2);
    if(way==1)
    {
    //display_board(1);
    //printf("Z");
    mines_func(r,c);
    //printf("A");
    init_board();
    //printf("B");
    start_t=clock();
    //printf("C");
    }
    if(my_data[r-1][c-1]=='*' && way==2)
    {
        game_over(r-1,c-1);
    }
    else if(board[r-1][c-1]=='F')
    {
        printf("You can't open a flagged cell!!\n");
        director(2);
    }
    else if(board[r-1][c-1]==0)
    {
        printf("Cell is already empty and open!\nPlease open another cell!\n");
        director(2);
    }
    else
        {
            board[r-1][c-1]=my_data[r-1][c-1];
            moves++;
            //printf("is %c\n\n",my_data[r-1][c-1]);
            //printf("and is %c\n\n",board[r-1][c-1]);
            open_adjacent_empty(r-1,c-1);
            //printf("check hi\n");
        }
        //printf("check w\n");
        int x;
            x=check_win();
        display_board(2);
}
int read_high_score()
{  FILE* f1;
int i=0;
    f1=fopen("highscore.txt","r");
     if (f1==NULL)
     {
         printf("High score file doesn't exist");
         exit(1);
     }
     while(!feof(f1))
     {
         fscanf(f1,"%[^,],%ld",HighScoreNames[i],&scorearray[i]);
         fscanf(f1,"\n");
i++;
     }
     close(f1);
return i;
}


void print_high_score()
{   system("cls");
    int i, j=1;
    printf("  NAME\t\t\t\tSCORE\n");

    for (i=scoresize; i>0;i--)
    printf("%d)%s\t\t\t%ld\n",j++,HighScoreNames[i-1],scorearray[i-1]);
    char c;
    fflush(stdin);
    printf("\nEnter any key to return to main menu\n");
    scanf("%c",&c);
    main_menu();

}

void main_menu()
{
    system("cls");
    printf("=========Minesweeper=========\n\n");
    printf("Enter your choice: \n");
    printf("1)Start a new game\n2)Load a saved game\n3)Display high scores\n4)Exit\n");
    int x;
    scanf("%d",&x);
    switch(x)
    {
    case 1:
        start_new_game();
        break;
    case 2:
        load_game();
        break;
    case 3:
        print_high_score();
        break;
    case 4:
        my_exit(2);
        break;
    }
}
int main()
{
   scoresize=read_high_score();
    main_menu();
    return 0;
}
