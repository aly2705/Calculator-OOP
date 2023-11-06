#pragma once
#include <iostream>
#include "Token.h"
using namespace std;


class Expression {
	string infix;
	char* postfix;

public:
	Expression();

	Expression(string expr);

	Expression(const Expression& expr);

	~Expression();

	Expression& operator=(const Expression& expr);

	void addToPostfix(Token token);
	
	void addToPostfix(char token);

	void convertInfixToPostfix();

	float evaluatePostfixResult();

	float evaluate();
};