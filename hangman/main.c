#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void addRope(char *part2);
void addHead(char *part3);
void addChest(char *part4);
void addBelly(char *part5);
void addLegs(char *part6);
void drawBase(char *part1, char *part2, char *part3, char *part4, char *part5, char *part6);

#define MAX_WORD_LENGTH 50

struct WordAndHints {
  char word[MAX_WORD_LENGTH];
  char hint[MAX_WORD_LENGTH];
};

int main() {
  char part1[13] = "\n__________\0";
  char part2[13] = "\n|         \0";
  char part3[13] = "\n|         \0";
  char part4[13] = "\n|         \0";
  char part5[13] = "\n|         \0";
  char part6[13] = "\n|         \0";

  srand(time(NULL));

  struct WordAndHints wordList[] = {
	  {"hello", "A form of greeting"},
	  {"elephant", "A large mammal with a trunk"},
	  {"pizza", "A popular Italian dish"},
	  {"beach", "Sandy shore by the sea"},
  };

  int index = rand() % 4;

  const char *word = wordList[index].word;
  const char *hint = wordList[index].hint;
  char guesedWord[strlen(word) + 1];

  for (int i = 0; word[i] != '\0'; i++) {
      guesedWord[i] = ' ';
      if(word[i + 1] == '\0') guesedWord[i + 1] == '\0';
  }


  unsigned int mistakesMade = 0;
  unsigned int correctGuess = 0;

  printf("\nWelcome to Hangman!\n");

  while (1) {
    printf("\n_____________________________\n");
    printf("_____________________________\n");
    printf("\nYour total tries left: %d", 5 - mistakesMade);
    printf("\nHint: %s", hint);
    printf("\nWord: %s\n\n", guesedWord);

    for (int i = 0; word[i] != '\0'; i++) {
      printf(" ");
    }

    for (int i = 0; word[i] != '\0'; i++) {
      printf("_ ");
    }

    printf("\n\n");
    printf("Enter a letter: ");
    char playerGuess;
    scanf(" %c", &playerGuess);

    for (int i = 0; word[i] != '\0'; i++) {

      if(guesedWord[i] != ' ') continue;

      if (playerGuess == word[i]) {
        printf("\nGood guess.");
        guesedWord[i] = word[i];
        correctGuess += 1;
        break;

      } else if (word[i + 1] == '\0') {
        printf("\nWrong guess.");
        mistakesMade += 1;
      }
    }

    if (mistakesMade == 1) addRope(part2);
    else if (mistakesMade == 2) addHead(part3);
    else if (mistakesMade == 3) addChest(part4);
    else if (mistakesMade == 4) addBelly(part5);
    else if (mistakesMade == 5) addLegs(part6);
    drawBase(part1, part2, part3, part4, part5, part6);

    if(mistakesMade == 5) {
      printf("\n\nYOU KILLED HIM!!! ;-;\n\n");
      break;
    }
    else if(correctGuess == strlen(word)) {
      printf("\n\nYOU SAVED HIM YAAAAAY!! :D\n\n");
      printf("\nWord: %s\n\n", guesedWord);

      for (int i = 0; word[i] != '\0'; i++) {
        printf(" ");
      }

      for (int i = 0; word[i] != '\0'; i++) {
        printf("_ ");
      }

      printf("\n\n");
      break;
    }
  }


  return 0;
}

void addRope(char *part2) { 
  part2[10] = '|';
}

void addHead(char *part3) {
  part3[10] = 'O';
}

void addChest(char *part4) {
  part4[9] = '/';
  part4[10] = '|';
  part4[11] = '\\';
}

void addBelly(char *part5) {
  part5[10] = '|';
}

void addLegs(char *part6) {
  part6[9] = '/';
  part6[10] = ' ';
  part6[11] = '\\';
}

void drawBase(char *part1, char *part2, char *part3, char *part4, char *part5, char *part6) {
  printf("%s", part1);
  printf("%s", part2);
  printf("%s", part3);
  printf("%s", part4);
  printf("%s", part5);
  printf("%s", part6);
  printf("\n\n");
}