#include <iostream>
#include <string>
#include <string.h>
#include <cmath>
#include "CharStack.h";
#include "NumberStack.h";
#include "Token.h"
#include "Expression.h";
using namespace std;

int main() {
	string input = ""; int counter = 0;
	cout << "Introduceti o expresie matematica: (pentru iesire introduceti 'exit')" << endl;

	while (input != "exit") {
		getline(cin, input);
		
		if (input != "exit") {
			Expression expression(++counter, input);
			int hasError = expression.evaluate();
			if (!hasError) cout << expression.getResult() << endl;
			else if (hasError == 1) cout << "Invalid expression" << endl;
			else if (hasError == 2) cout << "Invalid operation" << endl;
			cout << endl;
		}
		else cout <<"Expresii evaluate: "<< counter << endl;
	}
}