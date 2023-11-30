#pragma once
#include <iostream>
#include <string>
#include "NumberStack.h"
#include "CharStack.h"
#include "Token.h"
using namespace std;


class Expression {
	string infix;
	char* postfix;
	const int number;
	double result;

public:
	////////////////////////////////////////
	// Constructors
	Expression();

	Expression(int number, string expr);

	Expression(const Expression& expr);

	////////////////////////////////////////
	// Destructor
	~Expression();

	////////////////////////////////////////
	// Operator overloading
	Expression& operator=(const Expression& expr);

	Expression operator+(const Expression& expr);

	Expression operator-(const Expression& expr);

	friend ostream& operator<<(ostream& out, const Expression& expr);

	friend istream& operator>>(istream& in, Expression& expr);

	///////////////////////////////////////
	// Access methods
	string getInfix();

	void setInfix(string infix);

	char getPostfix(int index);

	void setPostfix(char* newPostfix);

	double getResult();

	void setResult(double result);

	int getNumber();

	////////////////////////////////////////
	// Generic methods
	void addToPostfix(Token token);
	
	void addToPostfix(char token);

	void removeSpacesFromInfix();

	// exit code 0 - successful parse
	// exit code 1 - error during parsing
	int convertInfixToPostfix();

	// exit code 0 - successful operation
	// exit code 1 - error during performing operations
	int evaluatePostfixResult();

	// exit code 0 - success
	// exit code 1 - invalid expression
	// exit code 2 - invalid operation encountered
	int evaluate();

};