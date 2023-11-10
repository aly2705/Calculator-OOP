#include <iostream>
#include <string>
#include <string.h>
#include <cmath>
#include "CharStack.h"
#include "NumberStack.h"
#include "Token.h"
#include "Expression.h"
using namespace std;

////////////////////////////////////////
// Constructors
Expression::Expression():number(0) {
	result = NULL;
	infix = "";
	postfix = nullptr;
}
Expression::Expression(int number, string expr):number(number) {
	result = NULL;
	infix = expr;
	postfix = nullptr;
}
Expression::Expression(const Expression& expr): number(expr.number) {
	result = expr.result;
	infix = expr.infix;

	if (expr.postfix != nullptr) {
		int copiedPostfixLength = strlen(expr.postfix);
		postfix = new char[copiedPostfixLength];
		for (int i = 0; i < copiedPostfixLength; i++) {
			postfix[i] = expr.postfix[i];
		}
	}
	else postfix = nullptr;
}

////////////////////////////////////////
// Destructor
Expression::~Expression() {
	if (postfix != nullptr) delete[] postfix;
}

////////////////////////////////////////
// Operator overloading
Expression& Expression::operator=(const Expression& expr) {
	if (this != &expr) {
		if (postfix != nullptr) {
			delete[] postfix;
			postfix = nullptr;
		};
		infix = expr.infix;
		result = expr.result;

		if (expr.postfix != nullptr) {
			int copiedPostfixLength = strlen(expr.postfix);
			postfix = new char[copiedPostfixLength + 1];
			for (int i = 0; i < copiedPostfixLength; i++) {
				postfix[i] = expr.postfix[i];
			}
			postfix[copiedPostfixLength] = '\0';
		}
		else postfix = nullptr;
	}
	return *this;
}

Expression Expression::operator+(const Expression& expr) {
	Expression copie;
	copie.infix = this->infix + "+(" + expr.infix + ")";
	return copie;
}

Expression Expression::operator-(const Expression& expr) {
	Expression copie;
	copie.infix = this->infix + "-(" + expr.infix + ")";
	return copie;
}

///////////////////////////////////////
// Access methods
float Expression::getResult() {
	return result;
}

void Expression::setResult(float result) {
	if (result == NULL) this->result = result;
}

string Expression::getInfix() {
	return infix;
}
void Expression::setInfix(string infix) {
	if (infix != "") {
		Token firstToken(infix[0]);
		if (firstToken.isSign() || firstToken.isOpenParanthesis() || firstToken.isDigit()) this->infix = infix;
	}
}

char Expression::getPostfix(int index) {
	if (index < strlen(postfix) && index >= 0 && postfix != nullptr) return postfix[index];
	// else throw exception;
}

void Expression::setPostfix(char* newPostfix) {
	if (postfix != nullptr) {
		delete[] postfix;
		postfix = nullptr;
	}
	if (newPostfix != nullptr) {
		int dim = strlen(newPostfix);

		postfix = new char[dim + 1];
		for (int i = 0; i < dim; i++) {
			postfix[i] = newPostfix[i];
		}
		postfix[dim] = '\0';
	}
	else postfix = nullptr;
}

int Expression::getNumber() {
	return number;
}


////////////////////////////////////////
// Generic methods
void Expression::addToPostfix(Token token) {
	if (postfix != nullptr) {
		int postfixSize = strlen(postfix);
		char* buffer = new char[postfixSize];
		for (int i = 0; i < postfixSize; i++) {
			buffer[i] = postfix[i];
		}

		delete[] postfix;
		postfix = new char[postfixSize + 2];
		for (int i = 0; i < postfixSize; i++) {
			postfix[i] = buffer[i];
		}
		postfix[postfixSize] = token.getValue();
		postfix[postfixSize + 1] = '\0';
		delete[] buffer;
	}
	else {
		postfix = new char[2];
		postfix[0] = token.getValue();
		postfix[1] = '\0';
	}
}
void Expression::addToPostfix(char token) {
	if (postfix != nullptr) {
		int postfixSize = strlen(postfix);
		char* buffer = new char[postfixSize];
		for (int i = 0; i < postfixSize; i++) {
			buffer[i] = postfix[i];
		}

		delete[] postfix;
		postfix = new char[postfixSize + 2];
		for (int i = 0; i < postfixSize; i++) {
			postfix[i] = buffer[i];
		}
		postfix[postfixSize] = token;
		postfix[postfixSize + 1] = '\0';
		delete[] buffer;
	}
	else {
		postfix = new char[2];
		postfix[0] = token;
		postfix[1] = '\0';
	}
}

void Expression::removeSpacesFromInfix() {
	if (infix != "") {
		int k = 0;
		char newInfix[100];

		for (int i = 0; i < infix.length(); i++) {
			Token t(infix[i]);
			if (!t.isSpace()) newInfix[k++] = infix[i];
		}
		newInfix[k++] = '\0';

		if (k > 1) infix = newInfix;
		else infix = "";
	}
}

// exit code 0 - successful parse
// exit code 1 - error during parsing
int Expression::convertInfixToPostfix() {
	removeSpacesFromInfix();
	if (infix == "") return 1;
	CharStack charStack;

	
	Token firstToken(infix[0]);
	if (!firstToken.isSign() && !firstToken.isOpenParanthesis() && !firstToken.isDigit()) return 1;
	

	for (int i = 0; i < infix.length(); i++) {
		Token t(infix[i]);
		
		if (t.isDigit() || t.isPoint()) {
			addToPostfix(t);

			if (i + 1 < infix.length()) {
				Token nextTok(infix[i + 1]);
				if ((!nextTok.isPoint() && !nextTok.isDigit()) || i + 1 == infix.length()) {
					addToPostfix(Token::getDelimiter());
				}
			}
			else if (i + 1 == infix.length()) {
				addToPostfix(Token::getDelimiter());
			}
		}
		else if (t.isOpenParanthesis()) charStack.push('(');
		else if (t.isOperator()) {
			// here we manage the signed numbers in an expression after a paranthesis
			// => a 0 is inserted in postfix so (-x) will be converted in '0 x -'
			if(i>0){
				Token lastProcessedToken(infix[i - 1]);
				if (t.isSign() && lastProcessedToken.isOpenParanthesis()) {
					addToPostfix('0');
					addToPostfix(Token::getDelimiter());
				}
			}

			int stackSize = charStack.getSize();
			char lastValue = stackSize > 0 ? charStack.getValue(stackSize - 1) : 0;
			Token lastToken(lastValue);
			while (lastToken.operatorPrecedence() >= t.operatorPrecedence() && lastValue && !lastToken.isOpenParanthesis()) {
				char poppedValue = charStack.pop();
				addToPostfix(poppedValue);
				addToPostfix(Token::getDelimiter());

				stackSize = charStack.getSize();
				lastValue = stackSize > 0 ? charStack.getValue(stackSize - 1) : 0;
				lastToken.setValue(lastValue);
			}
			charStack.push(t.getValue());
		}
		else if (t.isClosingParanthesis()) {
			int stackSize = charStack.getSize();
			char lastValue = stackSize > 0 ? charStack.getValue(stackSize - 1) : 0;

			Token lastToken(lastValue);
			while (!lastToken.isOpenParanthesis()) {
				char poppedValue = charStack.pop();
				addToPostfix(poppedValue);
				addToPostfix(Token::getDelimiter());

				stackSize = charStack.getSize();
				lastValue = stackSize > 0 ? charStack.getValue(stackSize - 1) : 0;
				lastToken.setValue(lastValue);
			}
			charStack.pop();
		}
		else return 1;
		
	};
	int stackSize = charStack.getSize();
	while (stackSize > 0) {
		char poppedValue = charStack.pop();
		addToPostfix(poppedValue);
		if (stackSize - 1 > 0) addToPostfix(Token::getDelimiter());

		stackSize = charStack.getSize();
	}
	cout << postfix<<endl;

	return 0;
}

// exit code 0 - successful operation
// exit code 1 - error during performing operations
int Expression::evaluatePostfixResult() {
	NumberStack numStack;
	char* context = nullptr;

	char delimiter[2];
	if (Token::getDelimiter() == ' ') {
		strcpy_s(delimiter, " ");
	}
	else strcpy_s(delimiter, "_");

	char* sequence = strtok_s(postfix, delimiter, &context);
	while (sequence != NULL) {
		Token firstToken(sequence[0]);
		if (firstToken.isDigit()) numStack.push(strtof(sequence, NULL));
		if (firstToken.isOperator()) {
			// Get operands
			float a = numStack.pop();

			float b;
			if (numStack.getSize() > 0)
				b = numStack.pop();
			else b = 0;

			// Perform desired operation and push in the numStack
			if (firstToken.getValue() == '+') numStack.push(a + b);
			else if (firstToken.getValue() == '*') numStack.push(a * b);
			else if (firstToken.getValue() == '/') {
				if (a != 0) numStack.push(b / a);
				// finish with error if a division by 0 is tried
				else return 1;
			}
			else if (firstToken.getValue() == '-') numStack.push(b - a);
			else if (firstToken.getValue() == '^') numStack.push(pow(b, a));
			else if (firstToken.getValue() == '#') numStack.push(pow(b, 1 / a));
		}

		sequence = strtok_s(NULL, delimiter, &context);
	}
	// Last value in the stack will be the expression result
	this->result = numStack.pop();
	return 0;
}

// exit code 0 - success
// exit code 1 - invalid expression
// exit code 2 - invalid operation encountered
int Expression::evaluate() {
	int errorDuringParsing = convertInfixToPostfix();
	if (!errorDuringParsing) {
		int invalidOperation = evaluatePostfixResult();
		if (!invalidOperation) return 0;
		else return 2;
	}
	else return 1;
}

