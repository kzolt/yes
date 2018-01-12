#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <map>

#include "Logic.h"

// Constructors

Logic::Logic()
	: m_hiddenWord(getRandomWord()), m_currentTry(1), m_gameWon(false) { }

// Getters

int Logic::getMaxTries() const
{ 
	std::map<int, int> wordLengthToMaxTries{ {3, 4}, {4, 7}, {5, 10}, {6, 16}, {7, 20} };
	return wordLengthToMaxTries[getHiddenWordLength()]; 
}

int Logic::getCurrentTry() const { return m_currentTry; }
bool Logic::isGameWon() const { return m_gameWon; }

int Logic::getHiddenWordLength() const { return m_hiddenWord.length(); }
std::string Logic::getHiddenWord() const { return m_hiddenWord; }

// Setters

void Logic::setCurretyTry() { m_currentTry = (getMaxTries() - 1); }

// Public Methods

void Logic::reset()
{
	m_currentTry = 1;
	m_gameWon = false;
	m_hiddenWord = getRandomWord();
}

GuessStatus Logic::checkGuessValidity(std::string& guess) const
{
	if (guess == std::string("hiddenword"))
	{
		return GuessStatus::REQUEST_HIDDEN_WORD;
	}

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

std::string getRandomWord()
{
	int currentLine = 1;

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(1, 21);
	int randomNumber = dist(mt);

	std::ifstream file("res/words/words.txt");
	std::string line;

	while (std::getline(file, line))
	{
		if (currentLine == randomNumber)
		{
			return line;
		}

		++currentLine;
	}

	return line;
}
