#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_SIZE 10
char **board;
int N;

//common symbols
char symbols[3] = {'X', 'O', 'Z'};

//----------------------Board Setup---------------------------
void initializeBoard(int size) {
    N = size;
    board = (char **)malloc(N * sizeof(char *));
    for (int i = 0; i < N; i++) {
        board[i] = (char *)malloc(N * sizeof(char));
        for (int j = 0; j < N; j++) {
            board[i][j] = ' ';
        
        }
    }
}
void freeBoard() {
    for (int i = 0; i < N; i++) free(board[i]);
    free(board);
}

void displayBoard() {
    printf("\n"); //print row
    for (int i = 0; i < N; i++) {
       for (int j = 0; j < N; j++){
         printf(" %c ", board[i][j]);
         if(j <N - 1) printf("|");   
        }

        printf("\n"); //print seperator row
         if(i < N - 1){
            for(int j = 0; j < N; j++){
                printf("---");
                if(j < N - 1) printf("+");
            }
            printf("\n");
        }
    }
    printf("\n");
}

//-------------------Validation----------------------------
int isValidMove(int row, int col){
    if (row < 0 || row >= N) return 0;
    if (col < 0 || col >= N) return 0;
    if (board[row][col] != ' ') return 0;
    return 1;
}

//----------------------Logging----------------------------
void logMove(int player, int row, int col) {
    FILE *fp = fopen("move_log.txt", "a");
    if(fp) {
        fprintf(fp, "Player %d (%c) -> (%d, %d)\n", player, symbols[player - 1], row + 1, col + 1);
        fclose(fp);
    }

}
//---------------------Win check---------------------------
int checkWin(char symbol) {
    for(int i = 0; i < N; i++){
        int rowWin = 1;
	int colWin = 1;
        for(int j = 0; j < N; j++){
            if(board[i][j] != symbol) rowWin = 0;
            if(board[j][i] != symbol) colWin = 0;        }
    
    if (rowWin || colWin) return 1;
    }

return 0;
}

int checkDiagonalWin(char symbol) {
	int diag1 = 1, diag2 = 1;
        for (int i = 0; i < N; i++){
            if(board[i][i] != symbol) diag1 = 0;
            if(board[i][N - i - 1] != symbol) diag2 = 0;

	    }
return diag1 || diag2;
   }


//------------------------Draw check------------------------------
int checkDraw() {
    for (int i = 0; i < N; i++){
      for (int j = 0; j < N; j++){
       if(board[i][j] == ' ') return 0;
      }
    }
    return 1;
    
}

//-----------------------Get user move---------------------------
void getUserMove(int player){
	int row, col;
	while (1) {
		printf("Player %d (%c), enter your move (row col): ", player, symbols[player - 1]);
		scanf("%d %d", &row, &col);
		row--;
		col--;
		if(isValidMove(row, col)){
			board[row][col] = symbols[player - 1];
			logMove(player, row,col);
			break;
		}else{
			printf("Invalid move,Try again.\n");
		}
	}
}


void getComputerMove(int player){
	int row, col;
	do{
		row = rand() % N;
		col = rand() % N;
	}
	while (!isValidMove(row, col));
	board[row][col] = symbols[player - 1];
	printf("Computer (Player %d) played at (%d, %d)\n",player, row +1, col +1);
	logMove(player, row, col);
}

#endif