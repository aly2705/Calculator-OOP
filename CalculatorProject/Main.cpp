#include <iostream>
#include <string>
#include <string.h>
#include <cmath>
#include <ctype.h>
using namespace std;

class CharStack {
private:
	int size;
	char* values;

public:
	CharStack() {
		values = nullptr;
		size = 0;
	}

	CharStack(const CharStack& s): CharStack() {
		if (s.values != nullptr && s.size > 0) {
			size = s.size;
			values = new char[s.size];
			for(int i=0; i< size ; i++){
				values[i] = s.values[i];
			}
		}
	}
	~CharStack() {
		if (values != nullptr && size > 0) {
			delete[] values;
			values = nullptr;
		};
	}
	CharStack& operator=(const CharStack& s) {
		if(this != &s){
		
			if (values != nullptr && size > 0) { 
				delete[] values;
				values = nullptr;
			};
		
			if (s.values != nullptr && s.size > 0) {
				size = s.size;
				values = new char[s.size];
				for (int i = 0; i < size; i++) {
					values[i] = s.values[i];
				}
			}
			else {
				size = 0;
				values = nullptr;
			}
		}
		return *this;
	}
	void push(char token) {
		if (values != nullptr && size > 0) {
			char* buffer = new char[size];
			for (int i = 0; i < size; i++) {
				buffer[i] = values[i];
			}
			delete[] values;
			values = new char[size + 1];
			for (int i = 0; i < size; i++) {
				values[i] = buffer[i];
			}
			values[size] = token;
			size = size + 1;
			delete[] buffer;
		}
		else {
			values = new char[1];
			size = 1;
			values[size - 1] = token;
		}
	}
	char pop() {
		if (values != nullptr && size > 0) {
			char* buffer = new char[size];
			for (int i = 0; i < size; i++) {
				buffer[i] = values[i];
			}
			delete[] values;
			values = new char[size-1];
			for (int i = 0; i < size-1; i++) {
				values[i] = buffer[i];
			}
			char poppedValue = buffer[size-1];
			size = size - 1;
			if (size == 0) {
				values = nullptr;
			}
			delete[] buffer;
			return poppedValue;

		}
		else {
			return -1;
		}
	}

	int getSize() {
		return size;
		
	}
	char getValue(int index) {
		if (index < size) {
			return values[index];
		}
		else return -1;
	}
};
class NumberStack {
private:
	int size;
	float* values;

public:
	NumberStack() {
		values = nullptr;
		size = 0;
	}

	NumberStack(const NumberStack& s) : NumberStack() {
		if (s.values != nullptr && s.size > 0) {
			size = s.size;
			values = new float[s.size];
			for (int i = 0; i < size; i++) {
				values[i] = s.values[i];
			}
		}
	}
	~NumberStack() {
		if (values != nullptr && size > 0) {
			delete[] values;
			values = nullptr;
		};
	}
	NumberStack& operator=(const NumberStack& s) {
		if (this != &s) {

			if (values != nullptr && size > 0) {
				delete[] values;
				values = nullptr;
			};

			if (s.values != nullptr && s.size > 0) {
				size = s.size;
				values = new float[s.size];
				for (int i = 0; i < size; i++) {
					values[i] = s.values[i];
				}
			}
			else {
				size = 0;
				values = nullptr;
			}
		}
		return *this;
	}
	void push(float token) {
		if (values != nullptr && size > 0) {
			float* buffer = new float[size];
			for (int i = 0; i < size; i++) {
				buffer[i] = values[i];
			}
			delete[] values;
			values = new float[size + 1];
			for (int i = 0; i < size; i++) {
				values[i] = buffer[i];
			}
			values[size] = token;
			size = size + 1;
			delete[] buffer;
		}
		else {
			values = new float[1];
			size = 1;
			values[size - 1] = token;
		}
	}
	float pop() {
		if (values != nullptr && size > 0) {
			float* buffer = new float[size];
			for (int i = 0; i < size; i++) {
				buffer[i] = values[i];
			}
			delete[] values;
			values = new float[size - 1];
			for (int i = 0; i < size - 1; i++) {
				values[i] = buffer[i];
			}
			float poppedValue = buffer[size - 1];
			size = size - 1;
			if (size == 0) {
				values = nullptr;
			}
			delete[] buffer;
			return poppedValue;
		}
		else {
			return -1;
		}
	}
	int getSize() {
		return size;

	}
	float getValue(int index) {
		if (index < size) {
			return values[index];
		}
		else return -1;
	}

};
class Token {


};
bool isParanthesis(char t) {
	return (t == '(' || t == ')');
}
int precedence(char operatorToken) {
	if (operatorToken == '^' || operatorToken == '#') return 3;
	if (operatorToken == '*' || operatorToken == '/') return 2;
	if (operatorToken == '+' || operatorToken == '-') return 1;
}
int isOperator(char token) {
	return (token == '+' || token == '-' || token == '*' || token == '/' || token == '^' || token == '#');
}


float evaluateExpression(string expr) {
	CharStack s;

	string infix = expr;
	//string infix = "3*(4+5)-7";

	CharStack postfix;

	for (int i = 0; i < infix.length(); i++) {
		//cout << infix[i] << " token";
		//cout << (infix[i] == '(');
		if (infix[i] != ' ') {
			if (isdigit(infix[i]) || infix[i] == '.') {
				postfix.push(infix[i]);
				if ((i+1<infix.length() && !(infix[i+1] == '.') && !isdigit(infix[i + 1])) || i+1 == infix.length()) {
					postfix.push(' ');
				}
				
			}
			else if (infix[i] == '(' || infix[i]=='[') s.push('(');
			else if (isOperator(infix[i])) {
				int stackSize = s.getSize();

				char lastValue = stackSize > 0 ? s.getValue(stackSize - 1) : 0;
				while ((precedence(lastValue) >= precedence(infix[i])) && lastValue && lastValue != '(') {
					char poppedValue = s.pop();
					postfix.push(poppedValue);
					postfix.push(' ');

					stackSize = s.getSize();
					lastValue = stackSize > 0 ? s.getValue(stackSize - 1) : 0;
				}
				s.push(infix[i]);
			}
			else if (infix[i] == ')' || infix[i] == ']') {
				int stackSize = s.getSize();
				char lastValue = stackSize > 0 ? s.getValue(stackSize - 1) : 0;
				while (lastValue != '(') {
					char poppedValue = s.pop();
					postfix.push(poppedValue);
					postfix.push(' ');

					stackSize = s.getSize();
					lastValue = stackSize > 0 ? s.getValue(stackSize - 1) : 0;
				}
				s.pop();
			}
		}
	}
	int stackSize = s.getSize();
	while (stackSize > 0) {
		char poppedValue = s.pop();
		postfix.push(poppedValue);
		if(stackSize-1>0) postfix.push(' ');

		stackSize = s.getSize();
	}

	//cout << endl << "Postfix" << endl;
	//for (int i = 0; i < postfix.getSize(); i++) {
		//cout << postfix.getValue(i);
	//}
	//cout << endl;

	
	char* postfixStr = new char[postfix.getSize()+1];
	for (int i = 0; i < postfix.getSize(); i++) {
		postfixStr[i] = postfix.getValue(i);
	}
	postfixStr[postfix.getSize()] = '\0';


	NumberStack helper;
	char* context = nullptr;
	char* sequence = strtok_s(postfixStr, " ", &context);
	while (sequence != NULL){
		// cout << sequence << endl;
		if (isdigit(sequence[0])) helper.push(strtof(sequence, NULL));
		if (isOperator(sequence[0])) {
			float a = helper.pop();
			// cout << a << endl;

			float b = helper.pop();
			// cout << b << endl;
			if (sequence[0] == '+') helper.push(a + b);
			else if (sequence[0] == '*') helper.push(a * b);
			else if (sequence[0] == '/') helper.push(b / a);
			else if (sequence[0] == '-') helper.push(b - a);
			else if (sequence[0] == '^') helper.push(pow(b, a));
			else if (sequence[0] == '#') { 
				float c = 1 / a;
				helper.push(pow(b, c));
			};
		}

		sequence = strtok_s(NULL, " ", &context);
	} 
	return helper.pop();

		/*
	for (int i = 0; i < postfix.getSize(); i++) {
		//cout << postfix.getValue(i);
		char token = postfix.getValue(i);
		if (isdigit(token)) helper.push((float)(token - 48));
		if (isOperator(token)) {
			float a = helper.pop();
			//cout << a << endl;

			float b = helper.pop();
			//cout << b << endl;
			if (token == '+') helper.push(a + b);
			else if (token == '*') helper.push(a * b);
			else if (token == '/') helper.push(b / a);
			else if (token == '-') helper.push(b - a);
		}
	} 
	*/
	 
}

int main() {
	string input = "S";
	while (input != "E") {
		getline(cin, input);
		cout<<evaluateExpression(input)<<endl;
	}

	// Expression evaluation

	
	// 1) Scan infix expression
	// 2) Apply shunting yard for infix->postfix
	// 3) Compute postfix expression  
}