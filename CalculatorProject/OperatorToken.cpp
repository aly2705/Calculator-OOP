#include "OperatorToken.h"


OperatorToken::OperatorToken() : Token() {
};
OperatorToken::OperatorToken(char op) : Token(op) {};
OperatorToken::OperatorToken(Token t) {
	value = t.getValue();
};

int OperatorToken::operatorPrecedence() {
	if (value == '^' || value == '#') return 3;
	if (value == '*' || value == '/') return 2;
	if (value == '+' || value == '-') return 1;
}

bool OperatorToken::isValidOperator() {
	return value != '\0';
}

bool OperatorToken::operator>=(OperatorToken tok) {
	return this->operatorPrecedence() >= tok.operatorPrecedence();
};

bool OperatorToken::operator>(OperatorToken tok) {
	return this->operatorPrecedence() > tok.operatorPrecedence();

};

bool OperatorToken::operator<=(OperatorToken tok) {
	return this->operatorPrecedence() <= tok.operatorPrecedence();

};

bool OperatorToken::operator<(OperatorToken tok) {
	return this->operatorPrecedence() < tok.operatorPrecedence();

};

bool OperatorToken::operator==(OperatorToken tok) {
	return this->operatorPrecedence() == tok.operatorPrecedence();
};