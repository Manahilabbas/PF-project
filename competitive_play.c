#include <stdio.h>

// Bold high-intensity blue for hangman structure
#define BHBLU "\033[1;94m"

// Bold high-intensity red for hangman figure
#define BHRED "\033[1;91m"

// Reset color
#define RESET "\033[0m"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <mmsystem.h>


struct users {
    char name[20];
    int score; // Tracks the correct guesses
};

#define MAX_WORD_LENGTH 20
#define MAX_HINT_LENGTH 50
#define MAX_WORDS 25
#define MAX_TRIES 6

void displayWord(const char guessedWord[], int wordLength);
void hangman(int guesses);
void playTurn(struct users *player, const char *selectedWord, const char *selectedHint);
void sound();
void soundwrong();
void soundallcorrect();
void endsound();

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
    "large reptile", "something that occurs in rain", 
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
    struct users player1, player2;
    int flag = 0;

    // Seed the random number generator once, at the beginning
    srand(time(0));
    
    // Initialize players
    printf("Enter the name of player 1:\n");
    scanf("%s", player1.name);
    player1.score = 0;

    printf("Enter the name of player 2:\n");
    scanf("%s", player2.name);
    player2.score = 0;

    int mode;
    printf("Enter the mode\n 1. Easy\n 2. Medium\n 3. Hard\n");
    scanf("%d", &mode);
    
    printf("Game started between %s and %s\n", player1.name, player2.name);
    getchar(); // To consume the leftover newline from scanf

    // Play a specified number of rounds
    int rounds;
    printf("How many rounds would you like to play? ");
    scanf("%d", &rounds);

    while (flag < rounds) {
        int randomIndex1 = rand() % MAX_WORDS; // Random word for player 1
        int randomIndex2 = rand() % MAX_WORDS; // Random word for player 2

        const char *selectedWord1;
        const char *selectedHint1;

        const char *selectedWord2;
        const char *selectedHint2;

        // Select word for player 1
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
                return 1;
        }

        // Select word for player 2
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
                return 1;
        }

        // Player 1's turn
        playTurn(&player1, selectedWord1, selectedHint1);

        // Player 2's turn
        playTurn(&player2, selectedWord2, selectedHint2);

        // Increment round counter
        flag++;
    }

    // Display results
    if (player1.score > player2.score) {
        printf("%s won\n", player1.name);
        
    } else if (player2.score > player1.score) {
        printf("%s won\n", player2.name);
        
    } else {
        printf("Game tied\n");
    }

    printf("Game Over!\n");
    endsound();

    return 0;
}

void displayWord(const char guessedWord[], int wordLength) {
    printf("Word: ");
    int i;
    for (i = 0; i < wordLength; i++) {
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


void playTurn(struct users *player, const char *selectedWord, const char *selectedHint) {
    printf("%s's turn\n", player->name);
    printf("Hint: %s\n", selectedHint);
    printf("The word has %d letters.\n", strlen(selectedWord));

    int length = strlen(selectedWord);
    char guessedWord[MAX_WORD_LENGTH];
    memset(guessedWord, '-', length);
    guessedWord[length] = '\0';

    printf("\n%s\n", guessedWord);

    char guess;
    int tries = MAX_TRIES;
    int correctGuess;

    while (tries > 0) {
        printf("Guess the letter: ");
        scanf(" %c", &guess); // Add space before %c to consume any leftover newline
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


