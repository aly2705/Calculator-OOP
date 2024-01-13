
#include <cstring>
#include <iostream>
#include "Token.h"
using namespace std;

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
// Operator overloading
bool Token::operator!() {
	return value == delimiter;
}

bool Token::operator>=(Token tok) {
		return this->value >= tok.value;
};

bool Token::operator>(Token tok) {
		// compare ascii codes
		return this->value > tok.value;
};

bool Token::operator<=(Token tok) {
		return this->value <= tok.value;
};

bool Token::operator<(Token tok) {
		return this->value < tok.value;
};

bool Token::operator==(Token tok) {
		return this->value == tok.value;
};

ostream& operator<<(ostream& out, const Token& t) {
	
	out << t.value;
	return out;
};
istream& operator>>(istream& in, Token& t) {
	char tok;
	in >> tok;
	t.setValue(tok);
	return in;
};

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
bool Token::isSign() {
	return (value == '+' || value == '-');
}
