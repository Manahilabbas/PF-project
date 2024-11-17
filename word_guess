#include <stdio.h>

// Bold high-intensity blue for hangman structure
#define BHBLU "\033[1;94m"

// Bold high-intensity red for hangman figure
#define BHRED "\033[1;91m"

// Reset color
#define RESET "\033[0m"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include<windows.h>
#include<conio.h>

#define MAX_TRIES 6
#define MAX_WORD_LENGTH 20

void displayWord(const char guessedWord[], int wordLength);
void hangman(int guesses);
int processGuess(char guess, const char word[], char guessedWord[], int wordLength);

void sound();
void soundwrong();
void soundallcorrect();
void endsound();
int main() {
    char word[MAX_WORD_LENGTH];
    char guessedWord[MAX_WORD_LENGTH];
    int wordLength;
    int tries = MAX_TRIES;
    char guess;
    int total=0, score=0;

int highscore2 = 0;

// Open the file to read the high score
FILE *file = fopen("highscore2.txt", "r");
if (file) {
    fscanf(file, "%d", &highscore2); // Read the current high score
    fclose(file);
} else {
    // If the file doesn't exist, create it and initialize high score to 0
    file = fopen("highscore2.txt", "w");
    fprintf(file, "0");
    fclose(file);
}

printf("Current High Score: %d\n", highscore2);


while(1){
total++;

    printf("Enter the word to be guessed: ");
    char hidden_word[100];
    int i = 0;
    // Word masking input
    while (1) {
        char ch = getch();  // Get a character without echoing to the console
        if (ch == '\r') {   // Enter key pressed
            hidden_word[i] = '\0';
            break;
        } else if (ch == '\b') {  // Handle backspace
            if (i > 0) {
                i--;
                printf("\b \b");  // Move back, print space, move back again
            }
        } else {
            hidden_word[i++] = ch;
            printf("*");
        }
    }

    
    strncpy(word, hidden_word, MAX_WORD_LENGTH - 1); // Copy password to word and limit length
    word[MAX_WORD_LENGTH - 1] = '\0';
    wordLength = strlen(word);

    // Sanitize input
    for (i = 0; i < wordLength; i++) {
        if (!isalpha(word[i])) {
            printf("Invalid character detected! Only alphabetic characters are allowed.\n");
            return 1; // Exit the program or prompt again
        }
        word[i] = tolower(word[i]); // Convert to lowercase for consistency
    }

    memset(guessedWord, '_', wordLength);
    guessedWord[wordLength] = '\0';

    while (tries > 0) {
        printf("\nGuess the letter: ");
        scanf(" %c", &guess);  // Read single character with leading space to ignore newlines
        guess = tolower(guess); // Convert to lowercase

        // Process the guess and update the guessedWord
        int correctGuess = processGuess(guess, word, guessedWord, wordLength);

        if (correctGuess == 0) {
            tries--;
            printf("Incorrect guess. You have %d tries left.\n", tries);
            sound();
        }

        displayWord(guessedWord, wordLength);
        hangman(tries);

        if (strcmp(guessedWord, word) == 0) {
            printf("Congratulations! You've guessed the word: %s\n", word);
            score++;
             soundallcorrect();
            break;
        }

        if (tries == 0) {
            printf("Sorry, you've run out of tries. The word was: %s\n", word);
            soundwrong();
        }
    }
printf("do you want to play again: \n 1.yes \n 2. no");
int choice;
scanf("%d",&choice);
if (choice==2){
printf (" game played=%d \n game win=%d \n game loss=%d",total,score,total-score);
// Update the high score if the player's score exceeds it
if (score > highscore2) {
    printf("Congratulations! You've set a new high score: %d\n", score);
    FILE *file = fopen("highscore2.txt", "w");
    fprintf(file, "%d", score); // Write the new high score
    fclose(file);
} else {
    printf("High Score remains: %d\n", highscore2);
}

 endsound();
break;}
else continue;
}

    return 0;
}

int processGuess(char guess, const char word[], char guessedWord[], int wordLength) {
    int correctGuess = 0;
    for (int i = 0; i < wordLength; i++) {
        if (word[i] == guess && guessedWord[i] != guess) {
            guessedWord[i] = guess;
            correctGuess = 1;
        }
    }
    return correctGuess;
}

void displayWord(const char guessedWord[], int wordLength) {
    printf("Word: ");
    for (int i = 0; i < wordLength; i++) {
        printf("%c ", guessedWord[i]);
    }
    printf("\n");
}

void hangman(int guesses) {
    switch (guesses) {
        case 6:
            printf(BHBLU" ==----== \n"RESET);
            printf(BHBLU" |      | \n"RESET);
            printf(BHBLU"        | \n"RESET);
            printf(BHBLU"        | \n"RESET);
            printf(BHBLU"        | \n"RESET);
            printf(BHBLU"        | \n"RESET);
            break;
        case 5:
            printf(BHBLU" ==----== \n"RESET);
            printf(BHRED" |"     BHBLU"      | \n"RESET);
            printf(BHRED" O  "   BHBLU"    | \n"RESET);
            printf(BHBLU"        | \n"RESET);
            printf(BHBLU"        | \n"RESET);
            printf(BHBLU"        | \n"RESET);
            break;
        case 4:
            printf(BHBLU" ==----== \n"RESET);
            printf(BHRED" | "     BHBLU"     | \n"RESET);
            printf(BHRED" O "     BHBLU"     | \n"RESET);
            printf(BHRED" | "    BHBLU"     | \n"RESET);
            printf(BHBLU"        | \n"RESET);
            printf(BHBLU"        | \n"RESET);
            break;
        case 3:
            printf(BHBLU" ==----== \n"RESET);
            printf(BHRED" | "     BHBLU"     | \n"RESET);
            printf(BHRED" O "     BHBLU"     | \n"RESET);
            printf(BHRED" |\\ "    BHBLU"    | \n"RESET);
            printf(BHBLU"        | \n"RESET);
            printf(BHBLU"        | \n"RESET);
            break;
        case 2:
            printf(BHBLU" ==----== \n"RESET);
            printf(BHRED" | "     BHBLU"     | \n"RESET);
            printf(BHRED" O "     BHBLU"     | \n"RESET);
            printf(BHRED"/|\\"    BHBLU"     | \n"RESET);
            printf(BHBLU"        | \n"RESET);
            printf(BHBLU"        | \n"RESET);
            break;
            case 1:
            printf(BHBLU" ==----== \n"RESET);
            printf(BHRED" | "     BHBLU"     | \n"RESET);
            printf(BHRED" O "     BHBLU"     | \n"RESET);
            printf(BHRED"/|\\"    BHBLU"     | \n"RESET);
            printf(BHRED"/ "     BHBLU"      | \n"RESET);
            printf(BHBLU"        | \n"RESET);
            break;
            case 0:
            printf(BHBLU" ==----== \n"RESET);
            printf(BHRED" | "     BHBLU"     | \n"RESET);
            printf(BHRED" O "     BHBLU"     | \n"RESET);
            printf(BHRED"/|\\"    BHBLU"     | \n"RESET);
            printf(BHRED"/ \\"     BHBLU"     | \n"RESET);
            printf(BHBLU"        | \n"RESET);
            break;
    }
}
void sound()
{
	Beep(400,1000);
}
void soundwrong()
{
// Open the mp3 file
    mciSendString("open \"sound4.mp3\" type mpegvideo alias myMP3", NULL, 0, NULL);
        

    // Play the mp3 file (non-blocking)
    mciSendString("play myMP3", NULL, 0, NULL);
    // Wait for user input to stop playback
    while (1) {
        Sleep(1000); // Pause for 1 second between prints
        if (kbhit()) {
        	getchar();
        	break;
    	}
	}

    // Stop and close the mp3
    mciSendString("stop myMP3", NULL, 0, NULL);
    mciSendString("close myMP3", NULL, 0, NULL);
}

void soundallcorrect()
{
		// Open the mp3 file
    mciSendString("open \"sound2.mp3\" type mpegvideo alias myMP3", NULL, 0, NULL);
        

    // Play the mp3 file (non-blocking)
    mciSendString("play myMP3", NULL, 0, NULL);
    // Wait for user input to stop playback
    while (1) {
        Sleep(1000); // Pause for 1 second between prints
        if (kbhit()) {
        	getchar();
        	break;
    	}
	}

    // Stop and close the mp3
    mciSendString("stop myMP3", NULL, 0, NULL);
    mciSendString("close myMP3", NULL, 0, NULL);
}

void endsound()
{
		// Open the mp3 file
    mciSendString("open \"sound1.mp3\" type mpegvideo alias myMP3", NULL, 0, NULL);
        

    // Play the mp3 file (non-blocking)
    mciSendString("play myMP3", NULL, 0, NULL);
    // Wait for user input to stop playback
    while (1) {
        Sleep(1000); // Pause for 1 second between prints
        if (kbhit()) {
        	getchar();
        	break;
    	}
	}

    // Stop and close the mp3
    mciSendString("stop myMP3", NULL, 0, NULL);
    mciSendString("close myMP3", NULL, 0, NULL);
}
