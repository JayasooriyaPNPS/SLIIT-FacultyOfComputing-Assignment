#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 //maximize boar size (change as needed)
char board[10][10];
int N;

void initializedBoard(int size){
    N = size;
    for(int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            board[i][j] = ' ';
        }
    }
}
void printBoard() {
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("[%c]", board[i][j]);
        }
        printf("\n");
    }
}

int main(){
    initializedBoard(3);   // create 3*3 board
    printBoard();
    return 0;   //
}

void displayBoard() {
    for (int i = 0; i < N; i++) {
        //print row
        for (int j = 0; j < N; j++){
         printf(" %c ", board[i][j]);
         if(j <N - 1) pritnf("|");   
        }
        printf("\n");

        //print seperator row
        if(i < N - 1){
            for(int j = 0; j < N; j++){
                printf("----");
                if(j < N - 1) printf("+");
            }
            printf("\n");
        }
    }
    printf("\n");
}

//check validity of move
int isValidMove(int row, int col){
    //check if row and col are inside the board
    if(row < 0 || row >= N ) return 0;
    if(col < 0 || col >= N) return 0;
    if(board[row][col] != ' ') return 0;
    }
    return 1; //valid


//make a move
int makeMove(int row, int col, char symbol){
    if(isValidMove(row, col)){
        board[row][col] = symbol;
        return 1;  //success
    }
    return 0; //invalid
}
//log moves to File

void logMove(int player, int row, int col){
    FILE *fp = fopen("move_log.txt", "a");
    if(fp) {
        fprintf(fp, "Player %d >> (%d, %d)\n", player, row + 1, col + 1);
        fclose(fp);
    }

}
int checkWin(char symbol){
    for(int i = 0; i < N; i++){
        int rowWin = 1, colWin = 1;
        for(int j = 0; j < N; j++){
            if(board[i][j] != symbol) rowWin = 0;
            if(board[i][j] != symbol) colWin = 0;        }
    }
    if (rowWin || colWin) return 1;
}
int diag1 = 1, diag2 = 1;
   for(int i = 0; i < N; i++){
    if(board[i][j] != symbol) diag1 = 0;
    if(board[i][N - i - 1] != symbol) diag2 = 0;
}
return diag1 || diag2;

int checkDraw() {
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
       if(board[i][j] == ' ') return 0;
    return 1;

} 

void freeBoard() {
    for(int i = 0; i < N; i++) free(board[i]);
    free(board);
}



