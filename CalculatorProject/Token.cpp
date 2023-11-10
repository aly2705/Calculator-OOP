#include "Token.h"
#include <string.h>


////////////////////////////////////
// Static attribute initialization
char Token::delimiter = ' ';


////////////////////////////////////
// Constructors
Token::Token() {
	value = '\0';
}
Token::Token(char value) {
	this->value = value;
}

///////////////////////////////////
// Access Methods
char Token::getValue() {
	return value;
}
void Token::setValue(char value) {
	this->value = value;
}
char Token::getDelimiter() {
	return delimiter;
}
void Token::setDelimiter(char newDelimiter) {
	if (newDelimiter == ' ' || newDelimiter == '_') delimiter = newDelimiter;
}

///////////////////////////////////
// Generic methods
bool Token::isOpenParanthesis() {
	return (value == '(' || value == '[');
}
bool Token::isClosingParanthesis() {
	return (value == ')' || value == ']');
}
bool Token::isOperator() {
	return (value == '+' || value == '-' || value == '*' || value == '/' || value == '^' || value == '#');
}
bool Token::isDigit() {
	return (value >= '0' && value <= '9');
}
bool Token::isPoint() {
	return value == '.';
}
bool Token::isSpace() {
	return value == ' ';
}
int Token::operatorPrecedence() {
	if (isOperator()) {
		if (value == '^' || value == '#') return 3;
		if (value == '*' || value == '/') return 2;
		if (value == '+' || value == '-') return 1;
		return -1;
	}
	else return -1;
}
bool Token::isSign() {
	return (value == '+' || value == '-');
}
