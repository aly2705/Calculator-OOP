#pragma once


class Token {
private:
	char value;

public:
	Token();

	Token(char value);

	char getValue();

	void setValue(char value);

	int isOpenParanthesis();

	int isClosingParanthesis();

	int isOperator();

	int isDigit();

	int isPoint();

	int isSpace();

	int precedence();


};