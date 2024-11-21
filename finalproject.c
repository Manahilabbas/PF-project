#include <stdio.h>
//for compititive mode to store names of both player and scores
struct users {
    char name[20];
    int score; // Tracks the correct guesses
};

void displayWord(const char guessedWord[], int wordLength); // display - and word have been guessed by user aftr each turn
void hangman(int guesses); // to display hang man after each guess
int processGuess(char guess, const char word[], char guessedWord[], int wordLength);
// for two player mode to display the turn of user and get the word 

void sound(); // beep for every wrong guessed word
void soundwrong();// sound if user out of tries and does not guess word completely
void soundallcorrect();// sound when user guess the word correctly
void endsound(); // used in other modes for ending
void end_sound();// use for compititive ode for ending
void startsound(); // sound for start menu
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
// fnctions for all modes
void word_guess();
void competitive_play();
void solo_play();

#define MAX_WORD_LENGTH 20
#define MAX_HINT_LENGTH 50
#define MAX_WORDS 25
#define MAX_TRIES 6
// using char array to sore word for easy mediumand hard mode 
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



int main ()
    { 
	int a=1;
while(a){// using while so game will run continously untill user chose to exit..
	int choice;
    
	printf("Enter the mode u want to play\n");
	printf("1.Competitive mode\n");
	printf("2.Word Guess\n");
	printf("3.Solo Play\n");
	printf("4.Exit\n");
	startsound();
	scanf("%d",&choice);
	switch(choice)
	{
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
        printf ("Good Byee!!!");
        endsound();
         a=0;
			break;
		default:
			printf("ohhh no! this mode is not exist :( please chose again\n");
	}
}
}
//function to play solo play
void solo_play() {
    int level;
    int score =0, total = 0;

    int highscore1 = 0;

    // Open the file to read the high score
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

    
    getchar(); // To consume the leftover newline from scanf

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

        int length = strlen(selectedWord);// getting the length of string  to display the length and run the loop to chech the word
        printf("Hint: %s\n", selectedHint);// display the hint of word to user 
        printf("Length = %d\n", length);

        char guessedWord[MAX_WORD_LENGTH];
        memset(guessedWord, '-', length);// to initializ complete word to display with - of lenght of word
        guessedWord[length] = '\0';// set end of string with null charector
         
         char guess;
        int tries = MAX_TRIES;// initilized the tries with max 
        int correctGuess;//to chect if the user guessed correctly 

        displayWord(guessedWord, length);//display the word (how many letters have been guessed)
        hangman(tries);// passed that how many number of tries remain and display hangman accordingly

        while (tries > 0) //loop will break if user use his all tries
        {
            printf("Guess the letter: ");
            scanf(" %c", &guess); // Add space before %c to consume any leftover newline
            guess = tolower(guess);// display either user use uppercase letter or lowercase
            correctGuess = processGuess(guess, selectedWord, guessedWord, length);//the function that do the bellow commented work
            //it retuns 0 if user gueesed incorrrect word
            //correctGuess=0 initialize with zero to check if user guesed word corectly
            // int i;
            // for (i = 0; i < length; i++) { //processGuess(guess, selectedword, guessedWord, length);
            //     if (guess == selectedWord[i]) { //loops to chect every letter of word with thw word input by the user
            //         guessedWord[i] = guess; // change the owrd from - to word enter by user as it is corect at index i of selectedword
            //         correctGuess = 1; // chnage it with 1 to show user enter the correct word
            //     }
            // }

            if (correctGuess == 0) {//if user gused incorret word then correct guess will be 0 
                tries--;// if he guessed incorect he lost his 1 try
                printf("Incorrect guess. You have %d tries left.\n", tries);// mention how many tries he has left
                sound();// beep for incorrect guessed
            }

            displayWord(guessedWord, length);//if user guessed correctly then it will mention that word in place of -. we pass our guessedword string and lenght of word to display it
            hangman(tries);//display hang man on the basis of number of tries that has left

            if (strcmp(guessedWord, selectedWord) == 0) {// using string campairing function if all the element of guessedword replaced by selectedword it returns 1and if block will run else it will return zero and if block will nor execute.
                printf("Congratulations! You've guessed the word: %s\n", selectedWord);// user guesed all the word
                soundallcorrect();//play sound
                score++;//increased in score
                break;
            }

            if (tries == 0) {
                printf("Sorry, you've run out of tries. The word was: %s\n", selectedWord);// user use all his tries how he is nor able to guseed fusrther words display the he supposed to gussed 
                soundwrong();// play sound
            }
        }

        printf("Do you want to play again?\n");// ask the user if he wants to play again 
        printf("1. Yes\n2. No\n");
        int choice;
        scanf("%d", &choice);
        if (choice == 2) {// if he chose no so display his score how many round he play and how many wrong
            printf("Total games played: %d\nGames won: %d\nGames lost: %d\n", total, score, total - score);
            score=(score/total)*100;// calculate the score in percentage... I will explain in detaile why use percentage.
            // Update the high score if the player's score exceeds it
            if (score > highscore1) {// if current game score if higher then the set high score
                printf("Congratulations! You've set a new high score: %d\n", score);
                FILE *file = fopen("highscore1.txt", "w");
                fprintf(file, "%d", score); // Write the new high score
                fclose(file);
            } else {
                printf("High Score remains: %d\n", highscore1);
            }

            endsound();// play end sound
            break;// break the loop while(1)
        }
    }
}


// function for word guessed round
//this roud is almost same as solo play you might understand 
void word_guess() {
    char word[MAX_WORD_LENGTH];
    char guessedWord[MAX_WORD_LENGTH];
    int wordLength;
    int tries = MAX_TRIES;
    char guess;
    int total = 0, score = 0;

    int highscore2 = 0;

    // Open the file to read the high score
    FILE *file = fopen("highscore2.txt", "r");// other file to store high score of this round
    if (file) {
        fscanf(file, "%d", &highscore2); // Read the current high scoreand store in variable highscore2
        fclose(file);
    } else {
        // If the file doesn't exist, create it and initialize high score to 0
        file = fopen("highscore2.txt", "w");
        fprintf(file, "0");
        fclose(file);
    }

    printf("Current High Score: %d\n", highscore2);

    while (1) {
        total++;//to tackle that how many time user play

        printf("Enter the word to be guessed: ");// ask one user to enter word to guessed
        char hidden_word[100];
        int i = 0;
        // Word masking input..used to not display word enter by user
        while (1) {
            char ch = getch();  // Get a character without echoing to the console(input)
            if (ch == '\r') {   // Enter key pressed
                hidden_word[i] = '\0';//last of string
                break;
            } else if (ch == '\b') {  // Handle backspace
                if (i > 0) {
                    i--;//if user is on 5th place and enter backspace the place should be now 4th 
                    printf("\b \b");  // Move back, print space, move back again
                }
            } else {
                hidden_word[i++] = ch;//store the charector of user into string
                printf("*");//show * instead of that word
            }
        }
        printf("\n");

        strncpy(word, hidden_word, MAX_WORD_LENGTH - 1); // Copy hidden word to word and limit length
        word[MAX_WORD_LENGTH - 1] = '\0';//last charector of string must be null chrector
        wordLength = strlen(word);

        // Sanitize input
        for (i = 0; i < wordLength; i++) {
            if (!isalpha(word[i])) {// if user enter other cherectors other then alphabets (ctype library function) return 1 for alphabets and return 0 for non_alphabets  !0=1
                printf("Invalid character detected! Only alphabetic characters are allowed.\n");
                return; // Exit the function or prompt again
            }
            word[i] = tolower(word[i]); // Convert to lowercase for consistency
        }

        memset(guessedWord, '_', wordLength);//set the - for gussing the word and show lengh of words
        guessedWord[wordLength] = '\0';// show the end after complete lengh of word wih -
         displayWord(guessedWord, wordLength);
            hangman(tries);
        while (tries > 0) {

            printf("\nGuess the letter: ");
            scanf(" %c", &guess);  // Read single character with leading space to ignore newlines
            guess = tolower(guess); // Convert to lowercase
            // Process the guess and update the guessedWord
            int correctGuess = processGuess(guess, word, guessedWord, wordLength);// call a function if the user guesed word correctly . this will return 0 if user guessed incorrect word and return 1 if he gussed word correctly

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
            // Update the high score if the player's score exceeds it
            score=(score/i)*100;//calculate score in %
            if (score > highscore2) {
                printf("Congratulations! You've set a new high score: %d\n", score);
                FILE *file = fopen("highscore2.txt", "w");
                fprintf(file, "%d", score); // Write the new high score
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

void competitive_play() {
    struct users player1, player2;//structure variables for both functions
    int flag = 0;//initialize falg with zero to now how many rounds user have played
    player1.score = player2.score = 0;//initialize both persons score with 0

    // Seed the random number generator once, at the beginning
    srand(time(0));
    
    // Initialize players
    printf("Enter the name of player 1:\n");
    scanf("%s", player1.name);

    printf("Enter the name of player 2:\n");
    scanf("%s", player2.name);
    
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
        //using 2 random index for both players
        int randomIndex1 = rand() % MAX_WORDS; // Random word for player 1
        int randomIndex2 = rand() % MAX_WORDS; // Random word for player 2
//for player1
        const char *selectedWord1;
        const char *selectedHint1;
//for player2
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
                return;
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
                return;
        }

        // Player 1's turn
        playTurn(&player1, selectedWord1, selectedHint1);//calling a function

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
    end_sound();
}
//functions
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
//........................................................

void displayWord(const char guessedWord[], int wordLength) {
    printf("Word: ");
    for (int i = 0; i < wordLength; i++) {//display the word that is guessing by user it will display how many letters have been guessed by user and display remaining with _
        printf("%c ", guessedWord[i]);
    }
    printf("\n");
}
//............................................................
void hangman(int guesses) {//print hangman on the basis of leftover number of try
    switch (guesses) {
        case 6:// if user have 6 tries left
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
//.....................
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

    // Monitor for user input to stop playback
    while (!kbhit()) {
        Sleep(100); // Small delay to reduce CPU usage while waiting for input
    }

    // Stop and close the mp3 once user types something
    mciSendString("stop myMP3", NULL, 0, NULL);
    mciSendString("close myMP3", NULL, 0, NULL);
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

//..........................................................

void playTurn(struct users *player, const char *selectedWord, const char *selectedHint) {//for cometitive mode  for each player
    printf("%s's turn\n", player->name);
    printf("Hint: %s\n", selectedHint);//show the hint of the word to the player whose trun is gooing on
    printf("The word has %d letters.\n", strlen(selectedWord));//lenght

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
//....................





 
