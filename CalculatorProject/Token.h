#pragma once


class Token {
private:
	char value;
	static char delimiter;

public:
	////////////////////////////////////
	// Constructors
	Token();

	Token(char value);


	///////////////////////////////////
	// Access Methods
	char getValue();

	void setValue(char value);

	static char getDelimiter();

	static void setDelimiter(char newDelimiter);

	///////////////////////////////////
	// Generic methods
	bool isOpenParanthesis();

	bool isClosingParanthesis();

	bool isOperator();

	bool isDigit();

	bool isPoint();

	bool isSpace();

	bool isSign();

	int operatorPrecedence();
	
};