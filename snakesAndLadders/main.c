#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LADDERS_AND_SNAKES 9
#define GAP "      "

struct Snakes {
	int head;
	int tail;
} snakes[MAX_LADDERS_AND_SNAKES] = {
	{13, 7},
	{19, 4},
	{48, 14},
	{57, 36},
	{68, 49},
	{83, 61},
	{87, 66},
	{94, 88},
	{98, 84}
};

struct Ladder {
	int bottom;
	int top;
} ladders[MAX_LADDERS_AND_SNAKES] = {
	{6, 24},
	{10, 12},
	{11, 33},
	{20, 38},
	{40, 59},
	{45, 54},
	{64, 78},
	{72, 91},
	{86, 96}
};

void setSnakeOrLadderOrCounter(int counter, int i, int j, int board[10][10]);
void initialiseBoard(int board[10][10]);
void printBoard(int board[10][10], int p1_pos, int p2_pos);
int rollDice();
void waitForEnter();
int updatePos(int pos, int dice);

int main() {
	int board[10][10];
	int p1_pos = 0;
	int p2_pos = 0;
	int p1_turn = 1;

	initialiseBoard(board);

	while(1) {
		printf("\nPlayer %d move. Press Enter to roll dice: ", p1_turn ? 1 : 2);
		waitForEnter();

		if(p1_turn) p1_pos = updatePos(p1_pos, rollDice());
		else p2_pos = updatePos(p2_pos, rollDice());

		printf("\nPOSITION:\n");
		printf("        Player1: %d\n        Player2: %d\n\n", p1_pos, p2_pos);

		if(p1_pos == 100 || p2_pos == 100) {
			printf("\nPlayer %d wins!\n", p1_pos == 100 ? 1 : 2);
			printBoard(board, p1_pos, p2_pos);
			break;
		}

		printBoard(board, p1_pos, p2_pos);
		p1_turn = !p1_turn;
	}
	return 0;
}

void setSnakeOrLadderOrCounter(int counter, int i, int j, int board[10][10]) {
	for(int k=0; k<MAX_LADDERS_AND_SNAKES; k++) {
		if(counter == snakes[k].head) {
			board[i][j] = -(snakes[k].tail + 100);
			return;
		}
		else if(counter == ladders[k].bottom) {
			board[i][j] = -ladders[k].top;
			return;
		}
	}
	board[i][j] = counter;
}

void initialiseBoard(int board[10][10]) {
	int flip = 0;
	int counter = 100;

	for(int i=0; i<10; i++) {

		if(flip == 0) {
			for(int j=0; j<10; j++) {
				setSnakeOrLadderOrCounter(counter,i,j,board);
				counter -= 1;
			}
			flip = 1;
		}
		else if(flip == 1) {
			for(int j=9; j>=0; j--) {
				setSnakeOrLadderOrCounter(counter,i,j,board);
				counter -= 1;
			}
			flip = 0;
		}
	}
}

void printBoard(int board[10][10], int p1_pos, int p2_pos) {
	printf("\n");

	for(int i=0; i<10; i++) {
		for(int j=0; j<10; j++) {

			if(p1_pos == board[i][j]) {
				if(p1_pos == p2_pos) {
					printf("\033[44mP1\033[0m");
					printf("\033[43mP2\033[0m%s", GAP);
				}
				else {
					printf("\033[44m_P1\033[0m%s", GAP);
				}
				continue;
			}
			if(p2_pos == board[i][j]) {
				if(p1_pos == p2_pos) {
					printf("\033[44mP1\033[0m");
					printf("\033[43mP2\033[0m%s", GAP);
				}
				else {
					printf("\033[43m_P2\033[0m%s", GAP);
				}
				continue;
			}

			if(board[i][j] < 0) {
				if(board[i][j] < -100) {
					printf("\033[31mS%.2d%s\033[0m", -1 * (board[i][j] + 100), GAP);
				}
				else{
					printf("\033[32mL%.2d\033[0m%s", -1 * board[i][j], GAP);
				}
				continue;
			}
			printf("%.3d%s", board[i][j], GAP);
		}
		printf("\n\n");
	}
	printf("\n");
}

int rollDice() {
	srand(time(NULL));
	int dice = rand() % 6 + 1;
	printf("You rolled a %d\n", dice);
	return dice;
}

void waitForEnter() {
	char c;
	do {
		c = getchar();
	} while (c != '\n');
}

int updatePos(int pos, int dice) {
	int new_pos = pos + dice;
	if(new_pos > 100) {
		printf("You need %d to win", 100 - pos);
		return pos;
	}
	for(int i=0; i<MAX_LADDERS_AND_SNAKES; i++) {
		if(new_pos == snakes[i].head) {
			printf("\033[31mOOPS YOU GOT EATEN BY: S%.2d\033[0m\n", snakes[i].tail);
			return snakes[i].tail;
		}
		if(new_pos == ladders[i].bottom) {
			printf("\033[32mNICE! YOU CLIMBED: L%.2d\033[0m\n", ladders[i].top);
			return ladders[i].top;
		}
	}
	return new_pos;
}