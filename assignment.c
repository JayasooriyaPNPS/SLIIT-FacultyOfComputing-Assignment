#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    return row >= 0 && row < N && col >= 0 && col < N && board[row][col] == ' ';
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
	int rowWin = 1;
	int colWin = 1;
    for(int i = 0; i < N; i++){
        int rowWin = 1, colWin = 1;
        for(int j = 0; j < N; j++){
            if(board[i][j] != symbol) rowWin = 0;
            if(board[j][i] != symbol) colWin = 0;        }
    }
    if (rowWin || colWin) return 1;
}

int checkDiagonalWinn(char symbols) {
	int diag1 = 1, diag2 = 1;
        for (int i = 0; i < N; i++){
            if(board[i][i] != symbols) diag1 = 0;
            if(board[i][N - i - 1] != symbols) diag2 = 0;

	    }
return diag1 || diag2;
   }


//------------------------Draw check------------------------------
int checkDraw() {
    for (int i = 0; i < N; i++){
      for (int j = 0; j < N; j++){
       if(board[i][j] == ' ') return 0;
    return 1;
      }
    }
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
			printf("Player %d (%c) wins!\n", currentPlayer, symbols[currentPlayer - 1]);
			break;
		}
		if (checkDraw()) {
			displayBoard();
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
		getComputerMove(2);
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
		if (currentPlayer == 1)
			getUserMove(currentPlayer);
		else
			getComputerMove(currentPlayer);
		if (checkWin(symbols[currentPlayer - 1])) {
			displayBoard();
			printf("Player %d (%c) wins!\n", currentPlayer, symbols[currentPlayer - 1]);
			break;
		}
		if (checkDraw()) {
			displayBoard();
			printf("It's a Draw!\n");
			break;
		}
		currentPlayer = (currentPlayer % 3) + 1;
	}
}

//----------------------------Main------------------------------
int main (void) {
	int size, mode;
	srand(time(NULL));

	printf("Enter board size (3 to 10): ");
	scanf("%d", &size);
	if (size < 3 || size > 10) {
		printf("Invalid size.\n");
		return 1;
	}

	printf("Select mode:\n");
	printf("1. Two player (User vs User)\n");
	printf("2. User vs Computer\n");
	printf("3. Three Player\n");
	printf("Choice: ");
	scanf("%d", &mode);

	FILE *fp = fopen("move_log.txt", "w");
	if (fp) fclose(fp);

	initializeBoard(size);

	if (mode == 1) playTwoPlayers();
	else if (mode == 2) playVsComputer();
	else if (mode == 3) playThreePlayer();
	else 
		printf("Invalid mode selected.\n");

	freeBoard();
	return 0;

}


