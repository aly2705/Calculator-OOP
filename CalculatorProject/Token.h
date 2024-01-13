#pragma once
#include <iostream>
using namespace std;

class Token {
private:
	static char delimiter;

protected:
	char value;

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
	// Operator overloading

	// !token=true => token is the delimiter
	// !token=false => token is not the delimiter
	bool operator!();

	// if both tokens are operators => compare precedence
	// else compare ascii codes
	bool operator>=(Token tok);
	bool operator>(Token tok);
	bool operator<=(Token tok);
	bool operator<(Token tok);
	bool operator==(Token tok);


	friend ostream& operator<<(ostream& out, const Token& t);
	friend istream& operator>>(istream& in, Token& t);

	///////////////////////////////////
	// Generic methods
	bool isOpenParanthesis();

	bool isClosingParanthesis();

	bool isOperator();

	bool isDigit();

	bool isPoint();

	bool isSpace();

	bool isSign();
	
};