#include <stdio.h>

struct users {
    char name[20];
    int score; 
};


int processGuess(char guess, const char word[], char guessedWord[], int wordLength);
void displayWord(const char guessedWord[], int wordLength);
void hangman(int guesses); 

void sound(); 
void soundwrong();
void soundallcorrect();
void endsound(); 
void end_sound();
void startsound();
void playTurn(struct users *player, const char *selectedWord, const char *selectedHint);
// Bold high-intensity blue for hangman structure
#define BHBLU "\033[1;94m"

// Bold high-intensity red for hangman figure
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"

// Reset color
#define RESET "\033[0m"
// standard library functions... will explain 


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

const char *easyWordList[MAX_WORDS] = {
    "computer", "apple", "guitar", "library", "lion", 
    "biology", "football", "mountain", "chocolate", "ocean", 
    "eagle", "architecture", "jupiter", "nest", "dinosaur", 
    "rainbow", "microscope", "cat", "bed", "whale", 
    "table", "python", "gravity", "rose", "laptop"
};

const char *easyHintList[MAX_WORDS] = {
    "electronic device", "fruit", "musical instrument", "A place where books are kept", 
    "animal", "The science of life", "physical game", "natural place", "A sweet", "natural place", 
    "bird", "profession", "planet", "related to birds", 
    "large reptile", "something that occurs in ra in", 
    "A tool", "animal", "furniture", "mammal", 
    "furniture", "A popular programming language", 
    "force exerted by earth", "flower", 
    "electronic device"
};

const char *mediumWordList[MAX_WORDS] = {
    "engineer", "diamond", "bicycle", "planetarium", "volcano",
    "oxygen", "ecosystem", "photograph", "satellite", "galaxy",
    "amphibian", "constellation", "asteroid", "blueprint", "currency",
    "eclipse", "forestry", "histogram", "molecule", "symphony",
    "telescope", "architecture", "radiation", "astronomy", "sculpture"
};

const char *mediumHintList[MAX_WORDS] = {
    "designs and builds", "precious gemstone", "two-wheeled vehicle",
    "celestial observation", "erupts with lava",
    "breathable gas", "community of organisms", "camera image",
    "object in orbit", "star system",
    "land-water animal", "star pattern", "space rock",
    "detailed building plan", "money system",
    "shadowed event", "manages forests", "data graph",
    "chemical particle", "musical composition",
    "far-seeing instrument", "building design", "emitted energy",
    "study of space", "3D art form"
};

const char *hardWordList[MAX_WORDS] = {
    "photosynthesis", "quarantine", "cryptography", "hypothesis", "metamorphosis",
    "neuroscience", "antiquarian", "epistemology", "isotope", "bioinformatics",
    "telecommunication", "psychoanalysis", "thermodynamics", "infrastructure", "nanotechnology",
    "topography", "cytogenetics", "cartography", "symbiosis", "hydrodynamics",
    "bioluminescence", "circumnavigate", "phytoplankton", "paleontology", "microbiology"
};

const char *hardHintList[MAX_WORDS] = {
    "plant energy process", "isolation period", "secret writing science",
    "educated guess", "transformation process",
    "brain study", "collector of antiques", "study of knowledge",
    "variant of element", "biology and data",
    "long-distance communication", "mind analysis", "heat and energy",
    "basic physical structures", "small-scale technology",
    "land surface mapping", "study of chromosomes", "mapmaking process",
    "mutualistic relationship", "fluid in motion",
    "natural light emission", "sail around", "tiny marine plants",
    "study of fossils", "small organism study"
};



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

    while (flag < rounds) {int randomIndex1 = rand() % MAX_WORDS; // Random word for player 1
        int randomIndex2 = rand() % MAX_WORDS; // Random word for player 2

        const char *selectedWord1;
        const char *selectedHint1;

        const char *selectedWord2;
        const char *selectedHint2;

        switch (mode) {
            case 1:
                selectedWord1 = easyWordList[randomIndex1];
                selectedHint1 = easyHintList[randomIndex1];
                break;
            case 2:
                selectedWord1 = mediumWordList[randomIndex1];
                selectedHint1 = mediumHintList[randomIndex1];
                break;
            case 3:
                selectedWord1 = hardWordList[randomIndex1];
                selectedHint1 = hardHintList[randomIndex1];
                break;
            default:
                printf("Invalid mode\n");
                return;
        }

        switch (mode) {
            case 1:
                selectedWord2 = easyWordList[randomIndex2];
                selectedHint2 = easyHintList[randomIndex2];
                break;
            case 2:
                selectedWord2 = mediumWordList[randomIndex2];
                selectedHint2 = mediumHintList[randomIndex2];
                break;
            case 3:
                selectedWord2 = hardWordList[randomIndex2];
                selectedHint2 = hardHintList[randomIndex2];
                break;
            default:
                printf("Invalid mode\n");
                return;
        }
        
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
    scanf("%d", &level);getchar(); // To consume the leftover newline from scanf

    while (1) {
        total++;// how many timee will run means user play game that times
        srand(time(0));// for geeting random index
        int randomIndex = rand() % MAX_WORDS;// mode of max word makes sure that word hould be in range of 0 to 25

        const char *selectedWord;
        const char *selectedHint;

        switch (level) {
            case 1:
                selectedWord = easyWordList[randomIndex];//select word from list at indexrandom index
                selectedHint = easyHintList[randomIndex];//hint of that word is placed in same index of string of hint as sting of word placed
                break;
            case 2:
                selectedWord = mediumWordList[randomIndex];
                selectedHint = mediumHintList[randomIndex];
                break;
            case 3:
                selectedWord = hardWordList[randomIndex];
                selectedHint = hardHintList[randomIndex];
                break;
            default:
                printf("Invalid level\n");
                return;
        }

        int length = strlen(selectedWord);
        printf("Hint: %s\n", selectedHint);
        printf("Length = %d\n", length);
        
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
        printf("Do you want to play again?\n");// ask the user if he wants to play again 
        printf("1. Yes\n2. No\n");
        int choice;
        scanf("%d", &choice);
        if (choice == 2) {
            printf("Total games played: %d\nGames won: %d\nGames lost: %d\n", total, score, total - score);
		 if (score > highscore1) {
                printf("Congratulations! You've set a new high score: %d\n", score);
                FILE *file = fopen("highscore1.txt", "w");
                fprintf(file, "%d", score); 
                fclose(file);
            } else {
                printf("High Score remains: %d\n", highscore1);
            }

            endsound();// play end sound
            break;// break the loop while(1)
        }
    }

            //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>..
}


void word_guess() {
	char word[MAX_WORD_LENGTH];
    char guessedWord[MAX_WORD_LENGTH];
    int wordLength;
    int tries;
    char guess;
    int total = 0, score = 0;
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
while (1) {
        tries = MAX_TRIES;
        total++;

        printf("Enter the word to be guessed: ");
        char hidden_word[100];
        int i = 0;
        while (1) {
            char ch = getch();  
            if (ch == '\r') { 
                hidden_word[i] = '\0';
                break;
            } else if (ch == '\b') { 
                if (i > 0) {
                    i--;
                    printf("\b \b"); 
                }
            } else {
                hidden_word[i++] = ch;
                printf("*");
            }
        }
        printf("\n");

        strncpy(word, hidden_word, MAX_WORD_LENGTH - 1); 
        word[MAX_WORD_LENGTH - 1] = '\0';
        wordLength = strlen(word);

        for (i = 0; i < wordLength; i++) {
            if (!isalpha(word[i])) {
                printf("Invalid character detected! Only alphabetic characters are allowed.\n");
                return; 
            }
            word[i] = tolower(word[i]); 
        }
    printf("enetr hint:\n");
    char*hint;
    scanf("%s",hint);
    

        memset(guessedWord, '_', wordLength);
        guessedWord[wordLength] = '\0';
        printf("\n Hint: %s\n ",hint);
         displayWord(guessedWord, wordLength);
            hangman(tries);
        while (tries > 0) {

            printf("\nGuess the letter: ");
            scanf(" %c", &guess); 
            guess = tolower(guess); 
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
    printf("Do you want to play again: \n 1. Yes \n 2. No\n");
        int choice;
        scanf("%d", &choice);
        if (choice == 2) {
            printf("Game played=%d \nGame won=%d \nGame lost=%d\n", total, score, total - score);
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
	guess=tolower(guess);
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
void sound()
{
	Beep(400,1000);
}
//.........................
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
//..............................................

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
//................................................
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

//...................................................
void startsound() {
    // Open the mp3 file
    mciSendString("open \"sound5.mp3\" type mpegvideo alias myMP3", NULL, 0, NULL);
    
    // Play the mp3 file (non-blocking)
    mciSendString("play myMP3", NULL, 0, NULL);
}


//.............................................................
void end_sound()
{
		// Open the mp3 file
    mciSendString("open \"sound1.mp3\" type mpegvideo alias myMP3", NULL, 0, NULL);
    // Play the mp3 file (non-blocking)
    mciSendString("play myMP3", NULL, 0, NULL);
        Sleep(10000); 
    // Stop and close the mp3
    mciSendString("stop myMP3", NULL, 0, NULL);
    mciSendString("close myMP3", NULL, 0, NULL);
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
            printf(GRN" |"     BHBLU"      | \n"RESET);
            printf(GRN" O  "   BHBLU"    | \n"RESET);
            printf(BHBLU"        | \n"RESET);
            printf(BHBLU"        | \n"RESET);
            printf(BHBLU"        | \n"RESET);
            break;
        case 4:
            printf(BHBLU" ==----== \n"RESET);
            printf(GRN" | "     BHBLU"     | \n"RESET);
            printf(GRN" O "     BHBLU"     | \n"RESET);
            printf(GRN" | "    BHBLU"     | \n"RESET);
            printf(BHBLU"        | \n"RESET);
            printf(BHBLU"        | \n"RESET);
            break;
        case 3:
            printf(BHBLU" ==----== \n"RESET);
            printf(YEL" | "     BHBLU"     | \n"RESET);
            printf(YEL" O "     BHBLU"     | \n"RESET);
            printf(YEL" |"YEL"\\ "    BHBLU"    | \n"RESET);
            printf(BHBLU"        | \n"RESET);
            printf(BHBLU"        | \n"RESET);
            break;
        case 2:
            printf(BHBLU" ==----== \n"RESET);
            printf(YEL" | "     BHBLU"     | \n"RESET);
            printf(YEL" O "     BHBLU"     | \n"RESET);
            printf(YEL"/"YEL"|"YEL"\\"   BHBLU"     | \n"RESET);
            printf(BHBLU"        | \n"RESET);
            printf(BHBLU"        | \n"RESET);
            break;
        case 1:
            printf(BHBLU" ==----== \n"RESET);
            printf(RED" | "     BHBLU"     | \n"RESET);
            printf(RED" O "     BHBLU"     | \n"RESET);
            printf(RED"/"RED"|"RED"\\"   BHBLU"     | \n"RESET);
            printf(RED"/"       BHBLU"       | \n"RESET);
            printf(BHBLU"        | \n"RESET);
            break;
    
        case 0:
            printf(BHBLU " ==----== \n" RESET);
            printf(RED " | "     BHBLU "     | \n" RESET);
            printf(RED " O "     BHBLU "     | \n" RESET);
            printf(RED "/" RED "|" RED "\\" BHBLU "     | \n" RESET);
            printf(RED "/ \\ " BHBLU "    | \n" RESET);
            printf(BHBLU"        | \n"RESET);
            break;
       
    }
}

void displayWord(const char guessedWord[], int wordLength) {
    printf("Word: ");
    for (int i = 0; i < wordLength; i++) {
        printf("%c ", guessedWord[i]);
    }
    printf("\n");
}
int processGuess(char guess, const char word[], char guessedWord[], int wordLength) {//this function have been discussed in solo_play mode
    int correctGuess = 0;
    for (int i = 0; i < wordLength; i++) {
        if (word[i] == guess && guessedWord[i] != guess) {
            guessedWord[i] = guess;
            correctGuess = 1;
        }
    }
    return correctGuess;
}




 
