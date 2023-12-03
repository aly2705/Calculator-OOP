#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
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
		postfix = new char[strlen(expr.postfix)+1];
		strcpy_s(postfix, strlen(expr.postfix) + 1, expr.postfix);
		
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
			postfix = new char[strlen(expr.postfix) + 1];
			strcpy_s(postfix, strlen(expr.postfix) + 1, expr.postfix);

		}
		else postfix = nullptr;
	}
	return *this;
}

Expression Expression::operator+(const Expression& expr) {
	// returns an expression that has the infix set as the result of exp1.infix+exp2.infix
	Expression sumExpression;
	sumExpression.infix = this->infix + "+(" + expr.infix + ")";
	return sumExpression;
}

Expression Expression::operator-(const Expression& expr) {
	// returns an expression that has the infix set as the result of exp1.infix-exp2.infix
	Expression diffExpression;
	diffExpression.infix = this->infix + "-(" + expr.infix + ")";
	return diffExpression;
}

ostream& operator<<(ostream& out, const Expression& expr) {
	// display expression result
	double decimalPart = expr.result - (int)expr.result;
	int decimalsCount = 0;
	
	// show 4 decimals if number has decimalPart, else show number without decimals
	if (abs(decimalPart) > 0.0)
		out << std::fixed << std::setprecision(4) << expr.result;
	else out << std::defaultfloat << expr.result;

	return out;
}
istream& operator>>(istream& in, Expression& expr) {
	// set infix value from a stream
	string input;
	getline(in, input);

	expr.result = NULL;
	expr.infix = input;
	expr.postfix = nullptr;

	return in;
}

///////////////////////////////////////
// Access methods
double Expression::getResult() {
	return result;
}

void Expression::setResult(double result) {
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

char* Expression::getPostfix() {
	char* copy = nullptr;
	if (postfix != nullptr) {
		copy = new char[strlen(postfix) + 1];
		strcpy_s(copy, strlen(postfix) + 1, postfix);
	}
	return copy;
}

void Expression::setPostfix(char* newPostfix) {
	if (postfix != nullptr) {
		delete[] postfix;
		postfix = nullptr;
	}
	if (newPostfix != nullptr) {
		postfix = new char[strlen(newPostfix) + 1];
		strcpy_s(postfix, strlen(newPostfix) + 1, newPostfix);

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

void Expression::convertInfixToPostfix() {
	removeSpacesFromInfix();
	if (infix == "") throw exception("Expresie invalida");
	CharStack charStack;

	
	Token firstToken(infix[0]);
	if (!firstToken.isSign() && !firstToken.isOpenParanthesis() && !firstToken.isDigit()) 
		throw exception("Expresie invalida");;
	

	for (int i = 0; i < infix.length(); i++) {
		Token t(infix[i]);
		
		if (t.isDigit() || t.isPoint()) {
			addToPostfix(t);

			// Validations
			if (i > 0 && i + 1 < infix.length()) {
				
				Token nextTok(infix[i + 1]), lastTok(infix[i - 1]);			

				if (t.isPoint() && nextTok.isPoint()) {
					throw exception("Expresie invalida. Secventa .. nu poate fi recunoscuta");
				}

				if (t.isPoint() && (!nextTok.isDigit() || !lastTok.isDigit())) {
					throw exception("Expresie invalida. Punctul trebuie precedat si succedat de cifre");
				}
				
			}

			// Decisions
			if (i + 1 < infix.length()) {
				Token nextTok(infix[i + 1]);
				

				if ((!nextTok.isPoint() && !nextTok.isDigit())) {
					addToPostfix(Token::getDelimiter());
				}
			}
			else if (i + 1 == infix.length()) {
				addToPostfix(Token::getDelimiter());
			}
		}
		else if (t.isOpenParanthesis()) { 
			if (i > 0) {
				// 5(...) will result in invalid expression
				Token lastProcessedToken(infix[i - 1]);
				if (lastProcessedToken.isDigit()) 
					throw exception("Expresie invalida! Numerele trebuie separate de paranteze printr-un operator");
				
			}
			charStack.push('('); 
		}
		else if (t.isOperator()) {
			
			if(i>0){

				// here we manage the signed numbers in an expression after a paranthesis
				// => a 0 is inserted in postfix so (-x) will be converted in '0 x -'
				Token lastProcessedToken(infix[i - 1]);
				if (t.isSign() && lastProcessedToken.isOpenParanthesis()) {
					addToPostfix('0');
					addToPostfix(Token::getDelimiter());
				}


				//consecutive operators are not allowed 
				if (lastProcessedToken.isOperator()) 
					throw exception("Expresie invalida. Operatorii consecutivi nu sunt permisi!");

				if (lastProcessedToken.isDigit() && t.isOpenParanthesis()) 
					throw exception("Expresie invalida. Numerele trebuie separate de paranteze printr-un operator");
			}


			
			int stackSize = charStack;  // cast to int will give the size
			char lastValue = stackSize > 0 ? charStack[stackSize - 1] : 0; // we use indexing operator to get the last value without actually popping it
			Token lastToken(lastValue);

			// t & lastToken are operators => relational operator will compare precedence
			while (lastToken >= t && lastValue && !lastToken.isOpenParanthesis()) {
				char poppedValue = charStack.pop();
				addToPostfix(poppedValue);
				addToPostfix(Token::getDelimiter());
				
				stackSize = charStack;
				lastValue = stackSize > 0 ? charStack[stackSize - 1] : 0;
				lastToken.setValue(lastValue);
			}
			charStack.push(t.getValue());
		}
		else if (t.isClosingParanthesis()) {
			if (i<infix.length()-1) {
				// (...)5 will result in invalid expression
				Token nextProcessedToken(infix[i + 1]);
				if (nextProcessedToken.isDigit())
					throw exception("Expresie invalida! Numerele trebuie separate de paranteze printr-un operator");
			}

			int stackSize = charStack;
			char lastValue = stackSize > 0 ? charStack[stackSize - 1] : 0;

			Token lastToken(lastValue);
			while (!lastToken.isOpenParanthesis() && stackSize>0) {
				char poppedValue = charStack.pop();
				addToPostfix(poppedValue);
				addToPostfix(Token::getDelimiter());

				stackSize = charStack;
				lastValue = stackSize > 0 ? charStack[stackSize - 1] : 0;
				lastToken.setValue(lastValue);
			}
			if (charStack.getSize() == 0) throw exception("Expresie invalida. Parantezele trebuie sa aiba pereche");
			charStack.pop();
		}
		else throw exception("Expresie invalida. S-au introdus caractere necunoscute.");
		
	};
	int stackSize = charStack;
	while (stackSize > 0) {
		char poppedValue = charStack.pop();
		addToPostfix(poppedValue);
		if (stackSize - 1 > 0) addToPostfix(Token::getDelimiter());

		stackSize = charStack;
	}
}


void Expression::evaluatePostfixResult() {
	NumberStack numStack;
	char* context = nullptr;

	char delimiter[2];
	if (Token::getDelimiter() == ' ') {
		strcpy_s(delimiter, " ");
	}
	else strcpy_s(delimiter, "_");

	// Each sequence delimited by the static delimiter from Token class (which is either ' ' or '_') 
	// can be a number or an operator and will be analised one by one
	char* sequence = strtok_s(postfix, delimiter, &context);
	while (sequence != NULL) {
		
		Token firstToken(sequence[0]);
		// found a number => push into stack
		if (firstToken.isDigit()) numStack.push(strtod(sequence, NULL));

		// found an operator => get last two operands and perform operation then push back to stack
		if (firstToken.isOperator()) {
			// Get operands
			double a = numStack.pop();

			double b;
			if (numStack.getSize() > 0)
				b = numStack.pop();
			else b = 0;

			// Perform desired operation and push in the numStack
			if (firstToken.getValue()== '+') numStack.push(a + b); 
			else if (firstToken.getValue() == '*') numStack.push(a * b);
			else if (firstToken.getValue() == '/') {
				if (a != 0) numStack.push(b / a);
				// finish with error if a division by 0 is tried
				else throw exception("Operatie invalida! Impartirea la 0 nu este permisa.");
			}
			else if (firstToken.getValue() == '-') numStack.push(b - a);
			else if (firstToken.getValue() == '^') {
				// finish with error if 0^0 is tried
				if (a != 0 && b != 0)
					numStack.push(pow(b, a));
				else throw exception("Operatie invalida! 0^0 nu poate fi efectuat.");
			}
			else if (firstToken.getValue() == '#') { 
				if (b < 0) 
					throw exception("Operatie invalida! Nu se poate efectua radical din numar negativ");

				else if(a == 0)
					throw exception("Operatie invalida! Nu se poate efectua radical de ordin 0");
				else numStack.push(pow(b, 1 / a));
			}
			
		}

		sequence = strtok_s(NULL, delimiter, &context);
	}
	// Last value in the stack will be the expression result
	this->result = numStack.pop();
}


void Expression::evaluate() {
	convertInfixToPostfix();
	evaluatePostfixResult();
	
}

