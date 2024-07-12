#include <stdio.h>
#include <stdlib.h>

char getPlayerMove(char allowedMoves[4]);
int isValidMove(char playerMove, char allowedMoves[4]);
char getComputerMove(char allowedMoves[4]);

int main() {
    printf("\nWelcome to rock paper scissors.\n");

    while(1) {

        printf("\n'r' for ROCK, 'p' for PAPER, 's' for SCISSOR, 'q' for EXIT\n");

        char allowedMoves[] = { 'r','p','s','q' };
        char playerMove = getPlayerMove(allowedMoves);
        char computerMove = getComputerMove(allowedMoves);

        if(playerMove == 'q') break;

        printf("\nYou chose %s", playerMove == 'r' ? "ROCK" : playerMove == 'p' ? "PAPER" : "SCISSOR");
        printf("\nComputer chose %s", computerMove == 'r' ? "ROCK" : computerMove == 'p' ? "PAPER" : "SCISSOR");

        if(playerMove == computerMove) printf("\n||||||--- IT'S A TIE! ---||||||");
        else if(playerMove == 'r' && computerMove == 's') printf("\n||||||--- YOU WON! ---||||||");
        else if(playerMove == 'p' && computerMove == 'r') printf("\n||||||--- YOU WON! ---||||||");
        else if(playerMove == 's' && computerMove == 'p') printf("\n||||||--- YOU WON! ---||||||");
        else printf("\n||||||--- YOU LOST! ---||||||");

        printf("\n\n");
    }
    return 0;
}

char getPlayerMove(char allowedMoves[4]) {
    char playerMove;
    do{
        printf("\nPick a valid move: ");
        scanf(" %c", &playerMove);
    } while(!isValidMove(playerMove, allowedMoves) && scanf("%*[^\n]") != EOF);
    return playerMove;
}

int isValidMove(char playerMove, char allowedMoves[4]) {
    for(int i=0; i<4; i++) {
        if(playerMove == allowedMoves[i]) return 1;
    }
    return 0;
}

char getComputerMove(char allowedMoves[4]) {
    return allowedMoves[rand() % 3];
}