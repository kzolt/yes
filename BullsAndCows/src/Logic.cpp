#include <string>
#include <map>

#include "Logic.h"

// Constructors

Logic::Logic(std::string hiddenWord)
	: m_hiddenWord(hiddenWord), m_currentTry(1), m_gameWon(false) { }

// Getters

int Logic::getMaxTries() const
{ 
	std::map<int, int> wordLengthToMaxTries{ {3, 4}, {4, 7}, {5, 10}, {6, 16}, {7, 20} };
	return wordLengthToMaxTries[getHiddenWordLength()]; 
}

int Logic::getCurrentTry() const { return m_currentTry; }
bool Logic::isGameWon() const { return m_gameWon; }

// Public Methods

void Logic::reset()
{
	m_currentTry = 1;
	m_gameWon = false;
}

GuessStatus Logic::checkGuessValidity(std::string& guess) const
{
	if (!isIsogram(guess))
	{
		return GuessStatus::NOT_ISOGRAM;
	}

	if (!isLowercase(guess))
	{
		return GuessStatus::NOT_LOWERCASE;
	}

	if (guess.length() != getHiddenWordLength())
	{
		return GuessStatus::WRONG_LENGTH;
	}

	return GuessStatus::OK;
}

int Logic::getHiddenWordLength() const
{
	return m_hiddenWord.length();
}

BullCowCount Logic::sumbitGuess(std::string& guess)
{
	m_currentTry++;

	BullCowCount bullCowCount;

	for (int i = 0; i < getHiddenWordLength(); i++)
	{
		for (int j = 0; j < getHiddenWordLength(); j++)
		{
			if (guess[j] == m_hiddenWord[i]) {
				if (i == j)
				{
					bullCowCount.m_Bulls++;
				}
				else 
				{
					bullCowCount.m_Cows++;
				}
			}
		}
	}

	if (guess == m_hiddenWord)
	{
		m_gameWon = true;
	}

	return bullCowCount;
}

// Private Methods

bool Logic::isIsogram(std::string& guess) const
{
	if (guess.length() <= 1) { return true; }

	std::map<char, bool> lettersSeen;

	for (char letter : guess)
	{
		letter = tolower(letter);

		if (lettersSeen[letter]) 
		{
			return false;
		}
		else
		{
			lettersSeen[letter] = true;
		}
	}

	return true;
}

bool Logic::isLowercase(std::string& guess) const
{

	for (char letter : guess)
	{
		if (!islower(letter)) { return false; }
	}

	return true;
}
