#pragma once
#include "Token.h"
class OperatorToken : protected Token
{
public:
	/////////////////////////////////////
	// Constructors
	OperatorToken();
	OperatorToken(char op);
	OperatorToken(Token t);

	/////////////////////////////////////
	// Operator overloading

	// all relational operators compare precedence
	bool operator>=(OperatorToken tok);
	bool operator>(OperatorToken tok);
	bool operator<=(OperatorToken tok);
	bool operator<(OperatorToken tok);
	bool operator==(OperatorToken tok);

	///////////////////////////////////
	// Generic methods

	int operatorPrecedence();

	// makes sure that the operator has a valid value
	bool isValidOperator();
};

