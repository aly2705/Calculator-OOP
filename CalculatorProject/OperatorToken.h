#pragma once
#include "Token.h"
class OperatorToken : protected Token
{
public:
	OperatorToken();
	OperatorToken(char op);
	OperatorToken(Token t);

	// compare precedence
	bool operator>=(OperatorToken tok);
	bool operator>(OperatorToken tok);
	bool operator<=(OperatorToken tok);
	bool operator<(OperatorToken tok);
	bool operator==(OperatorToken tok);

	///////////////////////////////////
	// Generic methods
	int operatorPrecedence();

	bool isValidOperator();
};

