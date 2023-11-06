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
	string input = "";
	cout << "Introduceti o expresie matematica: (pentru iesire introduceti 'exit')" << endl;
	while (input != "exit") {
		getline(cin, input);
		if (input != "exit") {
			Expression expression(input);
			cout << expression.evaluate() << endl;
			cout << endl;
		}
		else cout << "Se iese din program..."<<endl;
	}
}