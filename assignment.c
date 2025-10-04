#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10
char **board;
int N;

//common symbols
char symbols[3] = {'X', 'O', 'Z'};

//----------------------Board Setup---------------------------
void initializedBoard(int size){
    N = size;
    board = (char **)malloc(N * sizeof(char *));
    for (int i = 0; i < N; i++){
        board[i] = (char *)malloc(N * sizeof(char));
        for (int j = 0; j < N; j++){
            board[i][j] = ' ';
        
        }
    }
}
void freeBoard() {
    for(int i = 0; i < N; i++) free(board[i]);
    free(board);
}

void displayBoard() {
    printf("\n"); //print row
    for (int i = 0; i < N; i++) {
       for (int j = 0; j < N; j++){
         printf(" %c ", board[i][j]);
         if(j <N - 1) pritnf("|");   
        }

        printf("\n"); //print seperator row
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

//-------------------Validation----------------------------
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

//----------------------Logging----------------------------
void logMove(int player, int row, int col){
    FILE *fp = fopen("move_log.txt", "a");
    if(fp) {
        fprintf(fp, "Player %d >> (%d, %d)\n", player, row + 1, col + 1);
        fclose(fp);
    }

}
//---------------------Win check---------------------------
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

//------------------------Draw check------------------------------
int checkDraw() {
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
       if(board[i][j] == ' ') return 0;
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


void getComputerMove(){
	int row, col;
	do{
		row = rand() % N;
		col = rand() % N;
	}
	while (!isValidMove(row, col));
	board[row][col] = symbols[1];
	printf("Computer played at (%d, %d)\n", row +1, col +1);
	logMove(2, row, col);
}

//---------------------Game modes---------------------------------
void playTwoPlayers(){
	int currentPlayer = 1;
	while (1) {
		displayBoard();
		getUserMove(currentPlayer);
		if (checkWin(symbols[currentPlayer - 1])) {
			displayBoard();
			printf("Plater %d (%c) wins!\n", currentPlayer, symbols[currentPlayer - 1]);
			break;
		}
		if (checkDraw()) {
			displayboard();
			printf("It's a draw!\n");
			break;
		}
		currentPlayer = 3 - currentPlayer;
	}
}

void playVsComputer() {
	while (1) {
		displayBoard();
		getUserMove(1);
		if (checkWin(symbols[0])) {
			displayBoard();
			printf("You Win!\n");
			break;
		}
		if (checkDraw()) {
			displayBoard();
			printf("It's a draw!\n");
			break;
		}
		displayBoard();
		getComputerMove();
		if (checkWin(symbols[1])) {
			displayBoard();
			printf("Computer wins!\n");
			break;
		}
		if (checkDraw()) {
			displayBoard();
			printf("It's a draw!\n");
			break;
		}
	}
}

void playThreePlayer() {
	int currentPlayer = 1;
	while (1) {
		displayBoard();
		getUserMove(currentPlayer);
		if (checkWin(symbols[currentPlayer - 1])) {
			displayBoard();
			printf("Player %d (%c) wins!\n", currentPlayer, symbols[currentPlayer - 1]);
			break;
		}
		if (checkDraw()){
			displayBoard();
			printf("It's a draw!\n");
			break;
		}
		currentPlayer = (currentPlayer % 3) + 1;
	}
}

			

