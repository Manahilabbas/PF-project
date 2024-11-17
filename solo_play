#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <mmsystem.h>

#define MAX_WORD_LENGTH 20
#define MAX_HINT_LENGTH 50
#define MAX_WORDS 25
#define MAX_TRIES 6

// Bold high-intensity blue for hangman structure
#define BHBLU "\033[1;94m"

// Bold high-intensity red for hangman figure
#define BHRED "\033[1;91m"

// Reset color
#define RESET "\033[0m"

void displayWord(const char guessedWord[], int wordLength);
void hangman(int guesses);
void sound();
void soundwrong();
void soundallcorrect();
void endsound();

// words and hints for easy level
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

// words and hints for medium level
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

// words and hints for hard level
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
    int level;
    printf("Enter the level: \n 1. Easy\n 2. Medium\n 3. Hard\n");
    int score=0, total=0;

int highscore1 = 0;

// Open the file to read the high score
FILE *file = fopen("highscore1.txt", "r");
if (file) {
    fscanf(file, "%d", &highscore1); // Read the current high score
    fclose(file);
} else {
    // If the file doesn't exist, create it and initialize high score to 0
    file = fopen("highscore1.txt", "w");
    fprintf(file, "0");
    fclose(file);
}

printf("Current High Score: %d\n", highscore1);


    scanf("%d", &level);
    getchar(); // To consume the leftover newline from scanf

    while(1){
        total++;
        srand(time(0));
        int randomIndex = rand() % MAX_WORDS;

        const char *selectedWord;
        const char *selectedHint;

        switch (level) {
            case 1:
                selectedWord = easyWordList[randomIndex];
                selectedHint = easyHintList[randomIndex];
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
                return 1;
        }

        int length = strlen(selectedWord);
        printf("Hint: %s\n", selectedHint);
        printf("Length = %d\n", length);

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
                score++;
                break;
            }

            if (tries == 0) {
                printf("Sorry, you've run out of tries. The word was: %s\n", selectedWord);
                soundwrong();
            }
        }

        printf("Do you want to play again?\n");
        printf("1. Yes\n2. No\n");
        int choice;
        scanf("%d", &choice);
        if(choice == 2) {
            printf("Total games played: %d\nGames won: %d\nGames lost: %d\n", total, score, total - score);
            // Update the high score if the player's score exceeds it
if (score > highscore1) {
    printf("Congratulations! You've set a new high score: %d\n", score);
    FILE *file = fopen("highscore1.txt", "w");
    fprintf(file, "%d", score); // Write the new high score
    fclose(file);
} else {
    printf("High Score remains: %d\n", highscore1);
}

            endsound();
            break;
        }
    }
    return 0;
}
