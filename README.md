# **Hangman Game** 🎮
A Hangman game built in C that can be played in the Command Prompt or Visual Studio Code. The game features three modes: Competitive Mode, Word Guess Mode, and Solo Play Mode. It also includes sound effects using the WinMM library.
# Contributers
+ Manahil Abbas (24k-1026) -> Team Leader 
+ Armeen Azam (24k-0654)
+ Laiba Jamil (24k-0812)
+ Ariza Iqbal (24k-0854)
# Requirments
To run the Hangman game, ensure you have the following installed:
+ **Windows OS:**\
  The game is designed to run on Windows due to sound library compatibility.
+  **GCC Compiler:**\
  Install **MinGW** or another GCC-based compiler to compile the C code.
  [MinGW Download](https://sourceforge.net/projects/mingw/)
+  **WiMM Library:**\
  Used for sound effects. Ensure the `-lwinmm` flag is used during compilation.
+  **Visual Studio Code:**\
  Recommended IDE for running and debugging the game.
  [Download Visual Studio Code](https://code.visualstudio.com/download)
+  **C/C++ Extension for VS Code:**\
  Install the C/C++ extension by Microsoft for compiling and debugging C code in VS Code.

# Setup:
1. **On Command Prompt:**\
    **Navigate to the Hangman Project Folder:**\
  + Open File Explorer and locate your Hangman project folder.\
  + Click on the folder path bar at the top, type cmd, and press Enter. This will open Command Prompt in that folder.\

 2.**Compile the Game:**\
     Run the following command to compile the C file with sound support\
     `gcc -o play_sound filename.c -lwinmm`\
 3.**Run the game:**\
    After successful compilation Run:\
     `./play_sound`\

+ **On Visual Studio Code:**\
  Open VS Code and open the Hangman project folder:

Go to File > Open Folder and select the folder containing your Hangman project files, including the sound files.
Open the Terminal in VS Code:

Press Ctrl + ` (backtick) or go to Terminal > New Terminal.
Compile the Game:
In the terminal, run this command to compile your C file with sound support:






