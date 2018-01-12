/*	
*	Game Logic definitions
*/
#pragma once

struct BullCowCount
{
	int m_Bulls = 0;
	int m_Cows = 0;
};

enum class GuessStatus
{
	OK, NOT_ISOGRAM, NOT_LOWERCASE, WRONG_LENGTH, REQUEST_HIDDEN_WORD
};

// struct used by takeGuess() back in main translation unit to store values (don't ask why it's here)
struct ValidGuess
{
	std::string m_Guess;
	GuessStatus m_Status;
};

// General Logic Prototypes
class Logic
{
public:
	int getMaxTries() const;
	int getCurrentTry() const;
	int getHiddenWordLength() const;
	std::string getHiddenWord() const;

	void setCurretyTry();

	bool isGameWon() const;
	GuessStatus checkGuessValidity(std::string& guess) const;
	
	void reset();
	
	BullCowCount sumbitGuess(std::string& guess);

	Logic();

private:
	int m_currentTry;
	int m_maxTries;
	std::string m_hiddenWord;
	bool m_gameWon;

	bool isIsogram(std::string& guess) const;
	bool isLowercase(std::string& guess) const; 
};

std::string getRandomWord();