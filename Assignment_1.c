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
void displayBoard() {
}
