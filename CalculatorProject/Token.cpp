#include "Token.h"
#include <string.h>

char Token::delimiter = ' ';

Token::Token() {
	value = '\0';
}
Token::Token(char value) {
	this->value = value;
}
int Token::isOpenParanthesis() {
	return (value == '(' || value == '[');
}
int Token::isClosingParanthesis() {
	return (value == ')' || value == ']');
}
int Token::isOperator() {
	return (value == '+' || value == '-' || value == '*' || value == '/' || value == '^' || value == '#');
}
int Token::isDigit() {
	return (value >= '0' && value <= '9');
}
int Token::isPoint() {
	return value == '.';
}
int Token::isSpace() {
	return value == ' ';
}
int Token::precedence() {
	if (isOperator()) {
		if (value == '^' || value == '#') return 3;
		if (value == '*' || value == '/') return 2;
		if (value == '+' || value == '-') return 1;
		return -1;
	}
	else return -1;
}
int Token::isSign() {
	return (value == '+' || value == '-');
}
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


