#pragma once
#include <iostream>
#include <string>
#include <fstream>
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

	// returns an expression that has the infix set as the result of exp1.infix+exp2.infix
	Expression operator+(const Expression& expr);

	// returns an expression that has the infix set as the result of exp1.infix-exp2.infix
	Expression operator-(const Expression& expr);

	// display expression result
	friend ostream& operator<<(ostream& out, const Expression& expr);

	// set infix value from console stream
	friend istream& operator>>(istream& in, Expression& expr);

	// set infix value from txt file
	friend ifstream& operator>>(ifstream& f, Expression& expr);

	///////////////////////////////////////
	// Access methods
	string getInfix();

	void setInfix(string infix);

	char* getPostfix();

	void setPostfix(char* newPostfix);

	double getResult();

	void setResult(double result);

	int getNumber();

	////////////////////////////////////////
	// Generic methods
	void addToPostfix(Token token);
	
	void addToPostfix(char token);

	void addToInfix(string seq);

	void removeSpacesFromInfix();


	void convertInfixToPostfix();


	void evaluatePostfixResult();


	void evaluate();

};