#include <iostream>
#include <string>
#include <string.h>
#include <cmath>
#include "CharStack.h"
#include "NumberStack.h"
#include "Token.h"
#include "Expression.h"
using namespace std;


Expression::Expression() {
	infix = "";
	postfix = nullptr;
}
Expression::Expression(string expr) {
	infix = expr;
	postfix = nullptr;
}
Expression::Expression(const Expression& expr) {
	infix = expr.infix;

	if (expr.postfix != nullptr) {
		int copiedPostfixLength = strlen(expr.postfix);
		postfix = new char[copiedPostfixLength];
		for (int i = 0; i < copiedPostfixLength; i++) {
			postfix[i] = expr.postfix[i];
		}
	}
}
Expression::~Expression() {
	if (postfix != nullptr) delete[] postfix;
}
Expression& Expression::operator=(const Expression& expr) {
	if (this != &expr) {
		if (postfix != nullptr) delete[] postfix;
		infix = expr.infix;

		if (expr.postfix != nullptr) {
			int copiedPostfixLength = strlen(expr.postfix);
			postfix = new char[copiedPostfixLength];
			for (int i = 0; i < copiedPostfixLength; i++) {
				postfix[i] = expr.postfix[i];
			}
		}
	}
	return *this;
}
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

void Expression::convertInfixToPostfix() {
	CharStack charStack;

	for (int i = 0; i < infix.length(); i++) {
		Token t(infix[i]);
		if (!t.isSpace()) {
			if (t.isDigit() || t.isPoint()) {
				addToPostfix(t);

				if (i + 1 < infix.length()) {
					Token nextTok(infix[i + 1]);
					if ((!nextTok.isPoint() && !nextTok.isDigit()) || i + 1 == infix.length()) {
						addToPostfix(' ');
					}
				}
				else if (i + 1 == infix.length()) {
					addToPostfix(' ');
				}
			}
			else if (t.isOpenParanthesis()) charStack.push('(');
			else if (t.isOperator()) {
				int stackSize = charStack.getSize();
				char lastValue = stackSize > 0 ? charStack.getValue(stackSize - 1) : 0;

				Token lastToken(lastValue);
				while (lastToken.precedence() >= t.precedence() && lastValue && !lastToken.isOpenParanthesis()) {
					char poppedValue = charStack.pop();
					addToPostfix(poppedValue);
					addToPostfix(' ');

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
					addToPostfix(' ');

					stackSize = charStack.getSize();
					lastValue = stackSize > 0 ? charStack.getValue(stackSize - 1) : 0;
					lastToken.setValue(lastValue);
				}
				charStack.pop();
			}
		}
	}
	int stackSize = charStack.getSize();
	while (stackSize > 0) {
		char poppedValue = charStack.pop();
		addToPostfix(poppedValue);
		if (stackSize - 1 > 0) addToPostfix(' ');

		stackSize = charStack.getSize();
	}
}

float Expression::evaluatePostfixResult() {
	NumberStack numStack;
	char* context = nullptr;
	char* sequence = strtok_s(postfix, " ", &context);
	while (sequence != NULL) {
		Token firstToken(sequence[0]);
		if (firstToken.isDigit()) numStack.push(strtof(sequence, NULL));
		if (firstToken.isOperator()) {
			// Get operands
			float a = numStack.pop();
			float b = numStack.pop();

			// Perform desired operation and push in the numStack
			if (firstToken.getValue() == '+') numStack.push(a + b);
			else if (firstToken.getValue() == '*') numStack.push(a * b);
			else if (firstToken.getValue() == '/') numStack.push(b / a);
			else if (firstToken.getValue() == '-') numStack.push(b - a);
			else if (firstToken.getValue() == '^') numStack.push(pow(b, a));
			else if (firstToken.getValue() == '#') numStack.push(pow(b, 1 / a));
		}

		sequence = strtok_s(NULL, " ", &context);
	}
	return numStack.pop();
}

float Expression::evaluate() {
	convertInfixToPostfix();
	return evaluatePostfixResult();
}