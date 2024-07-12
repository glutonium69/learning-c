#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LADDERS_AND_SNAKES 9
#define GAP "      "

struct Snakes {
	int head;
	int tail;
};

struct Ladder {
	int bottom;
	int top;
};

void setSnakeOrLadderOrCounter(int counter, int i, int j, int board[10][10], struct Snakes snakes[], struct Ladder ladders[]);
void initialiseBoard(int board[10][10], struct Snakes snakes[], struct Ladder ladders[]);
void printBoard(int board[10][10], int p1_pos, int p2_pos);
int rollDice();
void waitForEnter();
void updatePos(int* p_pos, int dice, struct Snakes snakes[], struct Ladder ladders[]);

int main() {
	int board[10][10];
	int p1_pos = 0;
	int p2_pos = 0;
	int p1_turn = 1;
	
	struct Snakes snakes[MAX_LADDERS_AND_SNAKES] = {
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

	struct Ladder ladders[MAX_LADDERS_AND_SNAKES] = {
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

	initialiseBoard(board, snakes, ladders);

	while(1) {
		printf("\nPlayer %d move. Press Enter to roll dice: ", p1_turn ? 1 : 2);

		waitForEnter();

		int dice = rollDice();
		printf("You rolled a %d\n", dice);

		if(p1_turn) updatePos(&p1_pos, dice, snakes, ladders);
		else updatePos(&p2_pos, dice, snakes, ladders);

		printf("\nPOSITION:\n");
		printf("        Player1: %d\n        Player2: %d\n\n", p1_pos, p2_pos);

		if(p1_pos == 100) {
			printf("\nPlayer 1 wins!\n");
			printBoard(board, p1_pos, p2_pos);
			break;
		}
		if(p2_pos == 100) {
			printf("\nPlayer 2 wins!\n");
			printBoard(board, p1_pos, p2_pos);
			break;
		}
		
		printBoard(board, p1_pos, p2_pos);
		p1_turn = !p1_turn;
	}
	return 0;
}

void setSnakeOrLadderOrCounter(int counter, int i, int j, int board[10][10], struct Snakes snakes[], struct Ladder ladders[]) {
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

void initialiseBoard(int board[10][10], struct Snakes snakes[], struct Ladder ladders[]) {
	int flip = 0;
	int counter = 100;

	for(int i=0; i<10; i++) {

		if(flip == 0) {
			for(int j=0; j<10; j++) {
				setSnakeOrLadderOrCounter(counter,i,j,board,snakes,ladders);
				counter -= 1;
			}
			flip = 1;
		}
		else if(flip == 1) {
			for(int j=9; j>=0; j--) {
				setSnakeOrLadderOrCounter(counter,i,j,board,snakes,ladders);
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
	return rand() % 6 + 1;
}

void waitForEnter() {
	char c;
	do {
		c = getchar();
	} while (c != '\n');
}

void updatePos(int* p_pos, int dice, struct Snakes snakes[], struct Ladder ladders[]) {
	*p_pos += dice;
	if(*p_pos > 100) {
		*p_pos = 100;
		return;	
	}
	for(int i=0; i<MAX_LADDERS_AND_SNAKES; i++) {
		if(*p_pos == snakes[i].head) {
			*p_pos = snakes[i].tail;
			printf("\033[31mOOPS YOU GOT EATEN BY: S%.2d\033[0m\n", *p_pos);
			return;
		}
		if(*p_pos == ladders[i].bottom) {
			*p_pos = ladders[i].top;
			printf("\033[32mNICE! YOU CLIMBED: L%.2d\033[0m\n", *p_pos);
			return;
		}
	}
}