#include "Calculator.h"
using namespace std;

/*
*** Notita pentru parcurgerea mai usoara a proiectului:  

** EVALUAREA EXPRESIILOR
* Proiectul foloseste algoritmul Shunting Yard dezvoltat de Djikstra pentru a converti expresii usor inteligibile precum (2+3)*7 (numita notatie infix)
in expresii care tin cont de ordinea efectuarii operatiilor si pot fi calculate folosind o stiva de numere (expresia de mai sus devine '2 3 + 7 *' - numita
notatie postfix)
Daca infix-ul introdus este valid si nu apar exceptii la convertire, va exista o astfel de expresie postfix, care va fi evaluata pentru a determina rezultatul

** SCURTA DESCRIERE A CLASELOR IMPLEMENTATE:
* Expression - cu scop in convertirea si evaluarea expresiilor matematice
* Stack - clasa template implementata pentru a servi algoritmului de prelucrare a expresiilor

* Token - cu scop in realizarea validarilor caracterelor intalnite in timpul conversiilor si prelucrarilor
* OperatorToken - derivata din clasa Token, cu scopul de a encapsula logica pentru respectarea ordinii operatiilor

* App - clasa abstracta, defineste un comportament general al unei aplicatii de consola
* Calculator - clasa derivata din App, ce se ocupa de toata comunicarea cu utilizatorul (meniu+optiuni), precum si de extinderea functionalitatilor
aplicatiei prin permiterea evaluarii expresiilor din fisiere text, prin optiunea de afisare a rezultatelor intr-un nou fisier text si prin
serializarea datelor salvate de utilizator (variabile custom ale utilizatorului stocate intr-un fisier binar, datele avand corespondent 
in program un membru STL de tip map<string,double> pentru acces facil in timpul executiei; acestea pot fi folosite in evaluarea expresiilor)

** Evaluarea expresiilor propuse:
* Toate cele 10 expresii propuse in cerintele proiectului se afla deja in fisierul text Exp.txt si pot fi testate
* Procesarea argumentelor din linia de comanda se face separat la rularea fisierului executabil din terminal (ex: CalculatorProject.exe [4+(5-1)]*2))
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