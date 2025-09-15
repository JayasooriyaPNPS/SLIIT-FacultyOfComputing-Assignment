#include <stdio.h>
#include <stdlib.h>

char **board;
int N;
FILE *logFile;

//Initialize the board
void initializeBoard() {
	board = malloc(N * sizeof(char *));
	for (int i = 0; i < N; i++) {
		board[i] = malloc(N * sizeof(char));
		for (int j = 0; j < N; j++);
		board[i][j] = ' ';
	}
}
//Display Board
void printBoard(){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			printf("[%c]", board[i][j]);
		}
		printf("\n");
	}
}

int main (){
	initializedBoard(3);
	printBoard() {
		return 0;
	}

	void displayBoard(){
		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){
				printf(" %c ", board[i][j]);
				if(j < N - 1) printf("|");
			}
			printf("\n");

			if (i < N - 1){
				for (int j = 0; j < N; j++){
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
  if(row < 0 || row >= N) return 0;
  if(col < 0 || col >= N) return 0;
  if(board[row][col] != ' ') retur 0;
}
return 1; //valid
}

//make a move
int makeMove(int row, int col, char symbol){
	if(isValidMove
				
		

                


