#include "Calculator.h"
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
(vor putea fi implementate ca template in cadrul fazei 2)
*/

int main(int argc, char** argv) {
	Calculator* calculatorApp = new Calculator("Calculator App");
	
	if (argc > 1) {
		// Command line expression evaluation
		calculatorApp->processCmdArgs(argc, argv);
	}
	else {
		// Calculator App Full functionality
		calculatorApp->start();
		calculatorApp->run();
		calculatorApp->finish();
	}
	delete calculatorApp;
}