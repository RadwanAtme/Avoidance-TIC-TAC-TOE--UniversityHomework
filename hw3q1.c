/*-------------------------------------------------------------------------
    Include files:
-------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdbool.h>
/*-------------------------------------------------------------------------
    Constants and definitions:
-------------------------------------------------------------------------*/
#define N 11
#define PLAYER1 1
#define PLAYER2 2
#define LENGTH N*N
/*-------------------------------------------------------------------------
    Function declaration
-------------------------------------------------------------------------*/
void print_welcome();
void print_enter_board_size();
void print_board(char board[N][N], int n);
void print_player_turn(int player_index);
void print_error();
void print_winner(int player_index);
void print_tie();
void fill(char board[N][N],int size_of_board);
int play_the_game_player1(char board[N][N],int move_register[2][LENGTH],int size_of_board,int index);
int play_the_game_player2(char board[N][N],int move_register[2][LENGTH],int size_of_board,int index);
bool board_is_filled(char board[N][N],int size_of_board);
bool check_legal_move(char board[N][N],int size_of_board,int row,int col);
int fill_legal_move(char board[N][N],int move_register[2][LENGTH],char c,int row,int col,int index);
bool check_winner(char board[N][N],int size_of_board);
bool check_winner_row(char board[N][N],int size_of_board);
bool check_winner_col(char board[N][N],int size_of_board);
bool check_winner_diagonal(char board[N][N],int size_of_board);
bool check_winner_diagona2(char board[N][N],int size_of_board);
void play_the_game(char board[N][N],int size_of_board,int move_register[2][LENGTH]);
bool check_negativerow(char board[N][N],int move_register[2][LENGTH],int row,int index);
void undo(char board[N][N],int move_register[2][LENGTH],int index,int row);
bool check_tie(char board[N][N],int size_of_board);
int play_player1(char board[N][N],int size_of_board,int move_register[2][LENGTH],int index);
int play_player2(char board[N][N],int size_of_board,int move_register[2][LENGTH],int index);


/*-------------------------------------------------------------------------
    Implementation
-------------------------------------------------------------------------*/

//print welcome message
//1 lines
void print_welcome()
{
    printf("*** Welcome to AVOIDANCE TIC-TAC-TOE game ***\n\n");
}

//print message to enter board size
//1 lines
void print_enter_board_size()
{
    printf("Please enter board size (1 to %d):\n", N);
}

//print the board
//7 lines
void print_board(char board[N][N], int n)
{
    printf("\nCurrent board:\n");
    for (int i = 0; i < n; i++)
    {
        printf("|");
        for (int j = 0; j < n; j++)
        {
            printf("%c|", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//print a request for player with index "player_index" to move
//1 lines
void print_player_turn(int player_index)
{
    printf("\nPlayer ** %d **, enter next move:\n", player_index);
}

//print error message
//1 lines
void print_error()
{
    printf("Illegal move!!!, please try again:\n");
}

//print the winner
//1 lines
void print_winner(int player_index)
{
    printf("Player %d Wins! Hooray!\n", player_index);
}

//print message to announce there is a tie (no one wins)
//1 lines
void print_tie()
{
    printf("It's a tie!\n");
}

//main
//10 lines
int main()
{
    int move_register[2][LENGTH]={{0}};
    int size_of_board;
    print_welcome();
    print_enter_board_size();
    scanf("%d",&size_of_board);
    char board[N][N];
    fill(board,size_of_board);
    print_board(board,size_of_board);
    play_the_game(board,size_of_board,move_register);
    return 0;
}

//responsiple for orginaizing turns between player 1 and 2
//8 lines
void play_the_game(char board[N][N],int size_of_board,int move_register[2][LENGTH])
{
    int index=0;
    while(true)
    {
        index+=play_player1(board,size_of_board,move_register,index);
        if(index<0)
        {
            break;
        }
        index+=play_player2(board,size_of_board,move_register,index);
         if(index<0)
         {
             break;
         }
       }



    }

//checks resaults for player 1
//10 lines
int play_player1(char board[N][N],int size_of_board,int move_register[2][LENGTH],int index)
{
      print_player_turn(PLAYER1);
      int temp_index=play_the_game_player1(board,move_register,size_of_board,index);
        print_board(board,size_of_board);
        if(check_winner(board,size_of_board))
       {
         print_winner(PLAYER2);
         return -(index+2);//index+2 just to make sure the program stops
       }
       if(check_tie(board,size_of_board))
       {
           print_tie();
           return -(index+2);
       }
       return temp_index;

}

//checks resaults for player 2
//10 lines
int play_player2(char board[N][N],int size_of_board,int move_register[2][LENGTH],int index)
{
    print_player_turn(PLAYER2);
      int temp_index=play_the_game_player2(board,move_register,size_of_board,index);
        print_board(board,size_of_board);
        if(check_winner(board,size_of_board))
       {
         print_winner(PLAYER1);
         return -(index+2);
       }
       if(check_tie(board,size_of_board))
       {
           print_tie();
           return -(index+2);
       }
       return temp_index;

}

//registers the moves of player 1
//13 lines
int play_the_game_player1(char board[N][N],int move_register[2][LENGTH],int size_of_board,int index)
{
               int row,col;

        while(board_is_filled(board,size_of_board))
        {
            scanf("%d",&row);
            if(row<0)
            {
                if(check_negativerow(board,move_register,row,index))
                {
                    return row;
                }
                continue;
            }
            scanf("%d",&col);

            if(check_legal_move(board,size_of_board,row-1,col-1))
            {
               return fill_legal_move(board,move_register,'X',row-1,col-1,index);
            }

            else{
                print_error();
            }
        }
        return 0;
}



//registers the moves of player 2
//13 lines
int play_the_game_player2(char board[N][N],int move_register[2][LENGTH],int size_of_board,int index)
{


    int row,col;

        while(board_is_filled(board,size_of_board))
        {
            scanf("%d",&row);
            if(row<0)
            {
                if(check_negativerow(board,move_register,row,index))
                {
                    return row;
                }
                continue;
            }
            scanf("%d",&col);

            if(check_legal_move(board,size_of_board,row-1,col-1))
            {
               return fill_legal_move(board,move_register,'O',row-1,col-1,index);
            }

            else{
                print_error();
            }
        }
        return 0;
}


//initialize board
//3 lines
void fill(char board[N][N],int size_of_board)
{
    for (int row=0;row<size_of_board;row++){
        for(int col=0;col<size_of_board;col++)
    {
        board[row][col]='_';
    }
    }
}






//checks if undo is legal
//6 lines
bool check_negativerow(char board[N][N],int move_register[2][LENGTH],int row,int index)
{
    if(-row%2==0||-row>index)
                {
                    print_error();
                    return false;
                }
                else
                {
                    undo(board,move_register,index,row);
                    return true;
                }
}


//return the board to its previous state
//6 lines
void undo(char board[N][N],int move_register[2][LENGTH],int index,int row)
{
    while(row<0)
    {
        board[move_register[0][index-1]][move_register[1][index-1]]='_';
        move_register[0][index]=0;
        move_register[1][index]=0;
        index--;
        row++;
    }
}


//checks for illegal moves
//5 lines
bool check_legal_move(char board[N][N],int size_of_board,int row,int col)
{
    if(row>size_of_board||col>size_of_board)
    {
        return false;
    }
    if(board[row][col]!='_')
    {
        return false;
    }
    return true;
}


//used to fill when we know its legal move
//4 lines
int fill_legal_move(char board[N][N],int move_register[2][LENGTH],char c,int row,int col,int index)
{
                    board[row][col]=c;
                    move_register[0][index]=row;
                    move_register[1][index]=col;
                    return 1;
}



//checks if there is space for a move to be played
//5 lines
bool board_is_filled(char board[N][N],int size_of_board)
{
    for(int row=0;row<size_of_board;row++)
    {
        for(int col=0;col<size_of_board;col++)
        {
            if(board[row][col]=='_')
            {
                return true;
            }
        }
    }
    return false;
}

//checks if a tie is on the board
//5 lines
bool check_tie(char board[N][N],int size_of_board)
{
    for (int row=0;row<size_of_board;row++)
    {
        for(int col=0;col<size_of_board;col++)
        {
            if(board[row][col]=='_')
            {
                return false;
            }
        }
    }
    return true;
}



//checks if there is winner
//5 lines
bool check_winner(char board[N][N],int size_of_board)
{
  bool res1=check_winner_row(board,size_of_board);
  bool res2=check_winner_col(board,size_of_board);
  bool res3=check_winner_diagonal(board,size_of_board);
  bool res4=check_winner_diagona2(board,size_of_board);
  return(res1||res2||res3||res4);
}

//checks if there is a streak in the rows
//13 lines
bool check_winner_row(char board[N][N],int size_of_board)
{
    for(int row=0;row<size_of_board;row++){
        char letter=board[row][0];
        int count=0;
        for(int col=0;col<size_of_board;col++)
        {
            if(letter=='_')
            {
                break;
            }
            if(board[row][col]==letter)
            {
                count++;
            }
            else
            {
                break;
            }
        }
        if(count==size_of_board)
        {
            return true;
        }
}
return false;
}

//checks if there is streak in colomns
//13 lines
bool check_winner_col(char board[N][N],int size_of_board)
{
    for(int col=0;col<size_of_board;col++){
        char letter=board[0][col];
        int count=0;
        for(int row=0;row<size_of_board;row++)
        {
             if(letter=='_')
            {
                break;
            }
            if(board[row][col]==letter)
            {
                count++;
            }
            else
            {
                break;
            }
        }
        if(count==size_of_board)
        {
            return true;
        }
}
return false;
}

//check for streak in first diagonal
//12 lines
bool check_winner_diagonal(char board[N][N],int size_of_board)
{
    char dig1=board[0][0];
    bool flag1=true;
    int row=0,col=0;
    while(row<size_of_board&&col<size_of_board)
    {
        if(dig1=='_')
        {
            return false;
        }
        if(board[row][col]!=dig1)
        {
            flag1=false;
            break;
        }
        row++;
        col++;
    }
    return flag1;

}

//check for streak in second diagonal
//12 lines
bool check_winner_diagona2(char board[N][N],int size_of_board)
{
    int row=0,col=size_of_board-1;
    bool flag2=true;
    char dig2=board[0][size_of_board-1];
    while(row<size_of_board&&col>=0)
    {
        if(dig2=='_')
        {
            return false;
        }
        if(board[row][col]!=dig2)
        {
            flag2=false;
            break;
        }
        row++;
        col--;
    }
    return flag2;
}
