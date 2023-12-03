#include <iostream>
#include <string>
#include <string.h>
#include <iomanip>
#include <cmath>
#include "CharStack.h";
#include "NumberStack.h";
#include "Token.h"
#include "Expression.h";
using namespace std;

/*
*** Notita pentru parcurgerea mai usoara a proiectului:  
* Proiectul foloseste algoritmul Shunting Yard dezvoltat de Djikstra pentru a converti expresii usor inteligibile precum (2+3)*7 (numita notatie infix)
in expresii care tin cont de ordinea efectuarii operatiilor si pot fi calculate folosind o stiva de numere (expresia de mai sus devine '2 3 + 7 *' - numita
notatie postfix)
Daca infix-ul introdus este valid si nu apar exceptii la convertire, va exista o astfel de expresie postfix, care va fi evaluata pentru a determina rezultatul

* Proiectul e construit pe baza claselor
Expression - cu scop in convertirea si evaluarea expresiilor
Token - cu scop in realizarea validarilor caracterelor intalnite in timpul conversiilor si prelucrarilor
CharStack/NumberStack - cu functionailtati similare, implementate pentru a servi algoritmului de prelucrare a expresiilor 
(vor putea fi implementate ca template in cadrul fazei 2
*/

int main() {
	//////////////////////////
	// Calculator functionality
	string input = ""; int counter = 0;
	cout << "Introduceti o expresie matematica: (pentru iesire introduceti 'exit')" << endl;
	

	while (input != "exit") {
		getline(cin, input);
		
		if (input != "exit") {
			Expression expression(++counter, input);

			try {
				expression.evaluate();
				cout << expression << endl;
			}
			catch (exception& e) {
				cout << e.what() << endl;
			}
			cout << endl;
		}
		else cout <<"Expresii evaluate: "<< counter << endl;
	}
}