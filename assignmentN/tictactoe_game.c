#include "Tictactoe.h"

//---------------------Game modes---------------------------------
void playTwoPlayers(){
	int currentPlayer = 1;
	while (1) {
		displayBoard();
		getUserMove(currentPlayer);
		if (checkWin(symbols[currentPlayer - 1]) || checkDiagonalWin 
			(symbols[currentPlayer - 1])) { 
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
		if (checkWin(symbols[0]) || checkDiagonalWin(symbols[0])) {
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
		if (checkWin(symbols[1]) || checkDiagonalWin(symbols[1])) {
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
		if (checkWin(symbols[currentPlayer - 1]) || checkDiagonalWin
				(symbols[currentPlayer - 1])) {
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