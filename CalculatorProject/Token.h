#pragma once


class Token {
private:
	char value;
	static char delimiter;

public:
	// Constructors
	Token();

	Token(char value);


	// Access Methods
	char getValue();

	void setValue(char value);

	static char getDelimiter();

	static void setDelimiter(char newDelimiter);

	// Generic methods
	int isOpenParanthesis();

	int isClosingParanthesis();

	int isOperator();

	int isDigit();

	int isPoint();

	int isSpace();

	int precedence();

	int isSign();
};