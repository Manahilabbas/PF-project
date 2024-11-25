#include <stdio.h>

struct users {
    char name[20];
    int score; 
};


int processGuess(char guess, const char word[], char guessedWord[], int wordLength);

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <mmsystem.h>

void word_guess();
void competitive_play();
void solo_play();

#define MAX_WORD_LENGTH 20
#define MAX_HINT_LENGTH 50
#define MAX_WORDS 25
#define MAX_TRIES 6


int main() {
    int a = 1;
    while (a) { 
        int choice;

        startsound();

        
        printf("Enter the mode you want to play\n");
        printf("1. Competitive mode\n");
        printf("2. Word Guess\n");
        printf("3. Solo Play\n");
        printf("4. Exit\n");

        while (!kbhit()) {
            Sleep(100);  
        }

        endsound();
        getchar();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                competitive_play();
                break;
            case 2:
                word_guess();
                break;
            case 3:
                solo_play();
                break;
            case 4:
                printf("Goodbye!!!\n");
                endsound();
                a = 0;  
                break;
            default:
                printf("Oops! This mode doesn't exist. Please choose again.\n");
        }
    }

    return 0;
}

//>>>>>>>>>>>>>>>>>>>>>
void competitive_play() {
    struct users player1, player2;
    int flag = 0;
    player1.score = player2.score = 0;

    srand(time(0));
    
    printf("Enter the name of player 1:\n");
    scanf("%s", player1.name);

    printf("Enter the name of player 2:\n");
    scanf("%s", player2.name);
    
    int mode;
    printf("Enter the mode\n 1. Easy\n 2. Medium\n 3. Hard\n");
    scanf("%d", &mode);
    
    printf("Game started between %s and %s\n", player1.name, player2.name);
    getchar(); 
    int rounds;
    printf("How many rounds would you like to play? ");
    scanf("%d", &rounds);

    while (flag < rounds) {
 //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

        playTurn(&player1, selectedWord1, selectedHint1);

        playTurn(&player2, selectedWord2, selectedHint2);

        flag++;
    }
    if (player1.score > player2.score) {
        printf("%s won\n", player1.name);    
    } else if (player2.score > player1.score) {
        printf("%s won\n", player2.name);   
    } else {
        printf("Game tied\n");
    }
    printf("Game Over!\n");
    end_sound();
}

//function to play solo play
void solo_play() {
    int level;
    int score =0, total = 0;

    int highscore1 = 0;
    FILE *file = fopen("highscore1.txt", "r");
    if (file)// if fileexist or have some value 
     {
        fscanf(file, "%d", &highscore1); // Read the current high score
        fclose(file);
    } else {
        // If the file doesn't exist, create it and initialize high score to 0
        file = fopen("highscore1.txt", "w");
        fprintf(file, "0");
        fclose(file);
    }
    
printf("Enter the level: \n 1. Easy\n 2. Medium\n 3. Hard\n");
    printf("Current High Score: %d\n", highscore1);
    scanf("%d", &level);
//laiba>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
char guessedWord[MAX_WORD_LENGTH];
        memset(guessedWord, '-', length);
        guessedWord[length] = '\0';
         
         char guess;
        int tries = MAX_TRIES;
        int correctGuess;

        displayWord(guessedWord, length);
        hangman(tries);

        while (tries > 0) 
        {
            printf("Guess the letter: ");
            scanf(" %c", &guess); 
            guess = tolower(guess);
            correctGuess = processGuess(guess, selectedWord, guessedWord, length);
           
            if (correctGuess == 0) {
                tries--;
                printf("Incorrect guess. You have %d tries left.\n", tries);
                sound();
            }

            displayWord(guessedWord, length);
            hangman(tries);

            if (strcmp(guessedWord, selectedWord) == 0) {
                printf("Congratulations! You've guessed the word: %s\n", selectedWord);
                soundallcorrect();
                score++;
                break;
            }

            if (tries == 0) {
                printf("Sorry, you've run out of tries. The word was: %s\n", selectedWord);// user use all his tries how he is nor able to guseed fusrther words display the he supposed to gussed 
                soundwrong();
            }
        }
//laiba>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>..
}


void word_guess() {
int highscore2 = 0;
    FILE *file = fopen("highscore2.txt", "r");
    if (file) {
        fscanf(file, "%d", &highscore2);
        fclose(file);
    } else {
        file = fopen("highscore2.txt", "w");
        fprintf(file, "0");
        fclose(file);
    }

    printf("Current High Score: %d\n", highscore2);
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>..
if (score > highscore2) {
                printf("Congratulations! You've set a new high score: %d\n", score);
                FILE *file = fopen("highscore2.txt", "w");
                fprintf(file, "%d", score); 
                fclose(file);
            } else {
                printf("High Score remains: %d\n", highscore2);
            }
            endsound();
            break;
        } else {
            continue;
        }
    }
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void playTurn(struct users *player, const char *selectedWord, const char *selectedHint) {
    printf("%s's turn\n", player->name);
    printf("Hint: %s\n", selectedHint);
    printf("The word has %d letters.\n", strlen(selectedWord));

    int length = strlen(selectedWord);
    char guessedWord[MAX_WORD_LENGTH];
    memset(guessedWord, '-', length);
    guessedWord[length] = '\0';
    char guess;
    int tries = MAX_TRIES;
    int correctGuess;
    displayWord(guessedWord, length);
        hangman(tries);



    while (tries > 0) {
        printf("Guess the letter: ");
        scanf(" %c", &guess);
        correctGuess = 0;
int i;
        for ( i = 0; i < length; i++) {
            if (guess == selectedWord[i]) {
                guessedWord[i] = guess;
                correctGuess = 1;
            }
        }

        if (correctGuess == 0) {
            tries--;
            printf("Incorrect guess. You have %d tries left.\n", tries);
            sound();
        }

        displayWord(guessedWord, length);
        hangman(tries);

        if (strcmp(guessedWord, selectedWord) == 0) {
            printf("Congratulations! You've guessed the word: %s\n", selectedWord);
            soundallcorrect();
            player->score++;
            break;
        }

        if (tries == 0) {
            printf("Sorry, you've run out of tries. The word was: %s\n", selectedWord);
            soundwrong();
        }
    }
}


//....................





 
