#include <iostream>
#include <string>

#include "Logic.h"
#include "main.h"

// Made the game initialization on the heap cause it made sense at the time, rather than just making it a variable with a global scope
Logic* game = new Logic(); 

void printIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game!" << std::endl;
	std::cout << "         }   {         ___ " << std::endl;
	std::cout << "         (o o)        (o o) " << std::endl;
	std::cout << "  /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << " / | BULL |0            0|  COW | \\  " << std::endl;
	std::cout << "*  |----- |              | -----|  *  " << std::endl;
	std::cout << "   ^      ^              ^      ^     " << std::endl;
	std::cout << "Can you guess the " << game->getHiddenWordLength() << " letter isogram I'm Thinking of?" << std::endl;
}

// Prints Game Summary after game is done (doesn't just repeat the function above(yes ik it's a weird name choice))
void printGameSummary()
{
	if (game->isGameWon())
	{
		std::cout << "\nWell done! You've found the word." << std::endl;
	}
	else
	{
		std::cout << "\nBetter luck next time." << std::endl;
	}
}

// Takes user input then fucks about with it and puts it in a struct for ease of access later on (and also i figured it would be good to have multiple return types)
ValidGuess takeGuess()
{
	std::string userInput;

	std::cout << "\nYou are on try " << game->getCurrentTry() << "/" << game->getMaxTries() << std::endl;

	std::cout << "What is your guess" << std::endl;
	std::getline(std::cin, userInput);

	return { userInput, validateGuess(userInput) };
}

// takeGuess() uses this function to give the enumeration value of the struct mentioned above a value
GuessStatus validateGuess(std::string& guess)
{
	auto status = game->checkGuessValidity(guess);;

	switch (status) {
	case GuessStatus::NOT_ISOGRAM:
		std::cout << "\n" << guess << " is not an isogram\n" << std::endl;
		return status;
	case GuessStatus::WRONG_LENGTH:
		std::cout << "\nPlease enter a " << game->getHiddenWordLength() << " letter word\n" << std::endl;
		return status;
	case GuessStatus::NOT_LOWERCASE:
		std::cout << "\nThe word has to be lowercase\n" << std::endl;
		return status;
	case GuessStatus::REQUEST_HIDDEN_WORD:
		std::cout << "\nThe hidden word is " << game->getHiddenWord() << "\n" << std::endl;
	default:
		return status;
	}
}

// plays the game to completion
void playGame()
{
	ValidGuess guess;

	while (!game->isGameWon() && game->getCurrentTry() <= game->getMaxTries())
	{
		guess = takeGuess();

		if (guess.m_Status == GuessStatus::OK || guess.m_Status == GuessStatus::REQUEST_HIDDEN_WORD)
		{
			BullCowCount bullCowCount = game->sumbitGuess(guess.m_Guess);
			std::cout << " Bulls = " << bullCowCount.m_Bulls << "\n Cows  = " << bullCowCount.m_Cows << std::endl;

			if (guess.m_Status == GuessStatus::REQUEST_HIDDEN_WORD)
			{
				game->setCurretyTryHiddenWordCheat();
			}
		}
	}

	if (!game->isGameWon() && (game->getCurrentTry() - 1) == game->getMaxTries())
	{
		std::cout << "\nThe hidden word was: " << game->getHiddenWord() << std::endl;
	}

	printGameSummary();
	game->reset();
}

// pretty self explanitory
bool askToPlayAgain()
{
	char userInput[1];

	std::cout << "Would you like to play again with a different hidden word? y\\n" << std::endl;
	std::cin >> userInput[0];

	if (userInput[0] == 'n' || userInput[0] == 'N')
	{
		return true;
	}

	return false;
}

// main method/function cause ya need it
int main()
{	
	bool endGame = false;

	while (!endGame)
	{
		printIntro();
		playGame();
		endGame = askToPlayAgain();
	}

	delete game;
}