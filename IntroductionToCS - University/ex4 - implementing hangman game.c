/*********************
* Topaz Avraham
* 206842627
* ex_4
*********************/

#include <stdio.h>
#include <string.h>

#define ROWS 16
#define COLS 21

void sortStrings(char* options[], int optionsCounter);
void printMenu(char* options[], int optionsCounter);
void playGame(char* option, char* clue);
void printDrawSquare(int mistakes);
void initializeGuessWordArray(char* guessWord, int length, char* pLetter);
int countLengthWithoutSpaces(char* guessWord, int  optionLength);
void printGuessWord(char* guessWord, int length);
void updateGuessesArray(int* j, char guesses[], char letter);
void mistakesCounter(int* mistakes, char* option, char letter, int length, char* guesses);
int isVictorious(char* guessWord, char* option, int length, int, int);

void main() {

	//variables declarations
	char sentence[ROWS * COLS];
	char* options[ROWS], * clue = NULL, * p = NULL;
	int i = 0, optionsCounter = 0, digit;

	printf("Enter your words:\n");
	scanf("%[^\n]", sentence);

	//splitting the sentence the user entered into tokens, first token is the clue
	for (p = strtok(sentence, ":"); p != NULL; p = strtok(NULL, ",")) {
		if (p == sentence) {
			clue = p;

			//if it's the clue, continue to next iteration in order to not assign the clue as a word to play on
			continue;
		}
		options[i++] = p;
		(optionsCounter)++;
	}

	//call function to sort options in lexicographic order
	sortStrings(options, optionsCounter);

	printMenu(options, optionsCounter);
	scanf("%d", &digit);
	playGame(options[digit - 1], clue);
}

/***********************************************************************************
* Function Name: sortStrings
* Input: char* options[] (the words we can play on, int optionsCounter (the num of words we can play on)
* Output: nothing
* Function Operation: the function sorts all words in lexicographic order
***********************************************************************************/
void sortStrings(char* options[], int optionsCounter)
{
	char* temp;
	int result;

	//using bubble sort, we sort all the words the user entered
	for (int i = 0; i < optionsCounter; i++) {
		for (int j = i + 1; j < optionsCounter; j++) {

			result = strcmp(options[i], options[j]);

			//if the first word is bigger then the second word
			if (result > 0) {
				temp = options[i];
				options[i] = options[j];
				options[j] = temp;
			}
		}
	}
}

/***********************************************************************************
* Function Name: printMenu
* Input: char* options[] (the words we can play on, int optionsCounter (the num of words we can play on)
* Output: nothing
* Function Operation: the function prints all the words we can play on
***********************************************************************************/
void printMenu(char* options[], int optionsCounter) {
	printf("choose an option:\n");
	for (int i = 0; i < optionsCounter; i++) {
		printf("%d: %s\n", i + 1, options[i]);
	}
}

/***********************************************************************************
* Function Name: printDrawSquare
* Input: int mistakes (mistakes the user made so far)
* Output: nothing
* Function Operation: the function receives the num of mistakes and print the matching square
***********************************************************************************/
void printDrawSquare(int mistakes) {
	switch (mistakes) {

	case 0:
		printf(" _________________\n"
			"|                |\n"
			"|                |\n"
			"|                |\n"
			"|                |\n"
			"|                |\n"
			"|________________|\n");
		break;

	case 1:
		printf(" _________________\n"
			"|                |\n"
			"|  **            |\n"
			"|  **            |\n"
			"|                |\n"
			"|                |\n"
			"|________________|\n");
		break;

	case 2:
		printf(" _________________\n"
			"|                |\n"
			"|  **        **  |\n"
			"|  **        **  |\n"
			"|                |\n"
			"|                |\n"
			"|________________|\n");
		break;

	case 3:
		printf(" _________________\n"
			"|  --            |\n"
			"|  **        **  |\n"
			"|  **        **  |\n"
			"|                |\n"
			"|                |\n"
			"|________________|\n");
		break;

	case 4:
		printf(" _________________\n"
			"|  --        --  |\n"
			"|  **        **  |\n"
			"|  **        **  |\n"
			"|                |\n"
			"|                |\n"
			"|________________|\n");
		break;

	case 5:
		printf(" _________________\n"
			"|  --        --  |\n"
			"|  **        **  |\n"
			"|  **        **  |\n"
			"|                |\n"
			"| \\/\\/\\/\\/\\/\\/\\  |\n"
			"|________________|\n");
		break;
	}
}

/***********************************************************************************
* Function Name: playGame
* Input: char* option (the word to play), char* clue (the clue the user entered)
* Output: nothing
* Function Operation: the function execute the hangman game - details inside function
***********************************************************************************/
void playGame(char* option, char* clue) {

	//variables declarations
	int optionLength = strlen(option), mistakes = 0, i, usedClue = 0, j = 0, charactersEntered = 0;
	char* pLetter = option;


	//the word the user guessed by now
	char guessWord[COLS];

	/*
	guesses is COLS+5 size because the user can type 20 letters in the word + 5 mistakes
	(the extra index for /0 already reserved in COLS)
	*/
	char guesses[COLS + 5], letter;
	int guessesArraySize = sizeof(guesses) / sizeof(guesses[0]);

	//first, call function to put underscores in the word the user is about to fill
	initializeGuessWordArray(guessWord, optionLength, pLetter);

	//charactersCounter will hold the amount of characters in the word without counting spaces
	int charactersCounter = countLengthWithoutSpaces(guessWord, optionLength);

	//because this is the start of the game, the square is with 0 mistakes 
	printDrawSquare(mistakes);

	//we print the word the user filled by now- because this is the start, there are only underscores at the moment
	printGuessWord(guessWord, optionLength);
	printf("do you want a clue? press -> *\nThe letters that you already tried:\nplease choose a letter:\n");
	scanf(" %c", &letter);

	//if the user wants a clue
	if (letter == '*') {
		printf("the clue is: %s.\n", clue);
		usedClue = 1;
	}
	else {
		for (i = 0; i < optionLength; i++) {

			//if the letter is part of the word
			if (letter == option[i]) {

				//if the user already entered this letter before
				if (letter == guesses[i]) {
					printf("You've already tried that letter.");
					break;
				}
				//if not - we put the letter in the correct index in the word the user guessed by now and update charactersEntered
				else {
					guessWord[i] = letter;
					charactersEntered++;
				}
			}
		}
	}

	//call function to check if the letter is not part of the word, and to count the mistakes accordingly
	mistakesCounter(&mistakes, option, letter, optionLength, guesses);

	//then, repeat the exact same process over and over until the user reached 5 mistakes or won
	while (mistakes < 5) {

		//at the end of each guess, call function to check if the user won. if so, print and exit loop
		if (isVictorious(guessWord, option, optionLength, charactersCounter, charactersEntered)) {
			printDrawSquare(mistakes);
			printf("The word is %s, good job!", option);
			break;
		}

		/*
		repeat the exact same process described above
		until the user reached 5 mistakes or won
		*/

		printDrawSquare(mistakes);
		printGuessWord(guessWord, optionLength);
		updateGuessesArray(&j, guesses, letter);
		if (!usedClue) {
			printf("do you want a clue? press -> *\n");
		}
		printf("The letters that you already tried:");
		for (i = 0; i < j; i++) {
			if (i == 0) {
				printf(" ");
			}
			if (i >= 1) {
				printf(", ");
			}
			printf("%c", guesses[i]);
		}
		printf("\nplease choose a letter:\n");
		scanf(" %c", &letter);
		if (letter == '*') {
			//if the user didn't ask a clue before
			if (usedClue == 0) {
				printf("the clue is: %s.\n", clue);
				usedClue = 1;
			}
		}
		else {
			int letterGuessed = 0;
			for (i = 0; i < guessesArraySize; i++) {
				if (letter == guesses[i]) {
					printf("You've already tried that letter.\n");
					letterGuessed = 1;
				}
			}
			for (i = 0; i < optionLength; i++) {
				if (letterGuessed) {
					break;
				}
				if (letter == option[i]) {
					guessWord[i] = letter;
					charactersEntered++;
				}
			}

		}
		mistakesCounter(&mistakes, option, letter, optionLength, guesses);
	}

	//if user reach limit of mistakes, then print accordingly
	if (mistakes >= 5) {
		printDrawSquare(mistakes);
		printf("The word is %s, GAME OVER!\n", option);
	}
}

/***********************************************************************************
* Function Name: initializeGuessWordArray
* Input: char* guessWord (the word the user guessed so far) , int length (the size of the word)
*		 char* pLetter (char pLetter is a pointer to the word we play)
* Output: nothing
* Function Operation: the function initializes all characters in the array as _
***********************************************************************************/
void initializeGuessWordArray(char* guessWord, int length, char* pLetter) {
	const char SPACE = ' ';

	for (int i = 0; i < length; i++) {
		if (pLetter[i] != SPACE) {
			guessWord[i] = '_';
		}
		else {
			guessWord[i] = SPACE;
		}
	}
}

/***********************************************************************************
* Function Name: countLengthWithoutSpaces
* Input: char* guessWord (the word the user guessed so far), optionLength (size of the word)
* Output: int characterCounter (amount of character in the word without spaces)
* Function Operation: the function goes over all chars in guessWord count how many times the char is not space
***********************************************************************************/
int countLengthWithoutSpaces(char* guessWord, int  optionLength) {
	int characterCounter = 0;
	const char SPACE = ' ';
	for (int i = 0; i < optionLength; i++) {
		if (guessWord[i] != SPACE) {
			characterCounter++;
		}
	}
	return characterCounter;
}

/***********************************************************************************
* Function Name: printGuessWord
* Input: char* guessWord (the word the user guessed so far) , int length (the size of the word)
* Output: nothing
* Function Operation: the function prints the word the user guessed by now
***********************************************************************************/
void printGuessWord(char* guessWord, int length) {
	for (int i = 0; i < length; i++) {
		printf("%c", guessWord[i]);
	}
	printf("\n");
}

/***********************************************************************************
* Function Name: updateGuessesArray
* Input: int* j (j = the number of letters the user guessed by now)
		, char guesses[] (the letters the user guessed so far), char letter (the last guess)
* Output: nothing
* Function Operation: the function checks if the letter was guessed before,
					  if not it increases the num of letters he guessed
***********************************************************************************/
void updateGuessesArray(int* j, char guesses[], char letter) {
	int guessedBefore = 0;

	//go over all letters which were guessed before
	for (int i = 0; i < (*j) + 1; i++) {

		if (guesses[i] == letter || letter == '*') {
			guessedBefore = 1;
		}
	}

	//if user didn't guess the letter before
	if (guessedBefore == 0) {
		guesses[*j] = letter;
		(*j)++;
	}
}

/***********************************************************************************
* Function Name: mistakesCounter
* Input: int* mistakes , char* option (the word to guess) ,char letter (the last guess),
		 int length (size of the word), char* guesses (the letters the user guessed so far)
* Output: nothing
* Function Operation: the function checks if the last guess the user entered is part of the word
***********************************************************************************/
void mistakesCounter(int* mistakes, char* option, char letter, int length, char* guesses) {
	for (int i = 0; i < length; i++) {

		//if the letter is in the word
		if (letter == option[i]) {
			return;
		}
		//if the user already guessed that word
		else if (letter == guesses[i]) {
			return;
		}
		else if (letter == '*') {
			return;
		}
	}
	//if the function not returned by now, so the letter is a mistake
	(*mistakes)++;
}

/***********************************************************************************
* Function Name: isVictorious
* Input: char* guessWord (the word the user guessed so far) , int length (the size of the word)
*		 char* option (the real word to guess), int charactersCounter (amount of characters in the word)
*		 int charactersEntered (amount of characters the user guessed by now)
* Output: int 0/1 (1 if the user won the game, 0 otherwise)
* Function Operation: the function checks if all letters in the word the user guessed are the same as the real word
*					  it also checks if the exact same amount of characters were entered without spaces
*					  if so, it return 1 (victorious), 0 (loser) otherwise
***********************************************************************************/
int isVictorious(char* guessWord, char* option, int length, int charactersCounter, int charactersEntered) {

	if (charactersCounter != charactersEntered) {
		return 0;
	}
	for (int i = 0; i < length; i++) {
		if (guessWord[i] != option[i]) {
			return 0;
		}
	}
	return 1;
}
