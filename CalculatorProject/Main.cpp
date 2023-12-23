#define YELLOW_FC "\x1B[33m"
#define GREEN_FC "\x1B[32m"
#define RED_FC "\x1B[31m"
#define DEFAULT_FC "\x1B[0m"
#include <iostream>
#include <string>
#include <string.h>
#include <iomanip>
#include <cmath>
#include <map>
#include <conio.h>
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
(vor putea fi implementate ca template in cadrul fazei 2)
*/

class App {
private:
	string appName;
public:
	App() {
		appName = "APP";
	}
	App(string appName) {
		this->appName = appName;
	}
	virtual void start() {
		cout << endl << YELLOW_FC << "------------ " << appName<<" ------------"<<DEFAULT_FC<<endl;
	};

	virtual void displayMainMenu() = 0;
	virtual void run() {
		cout << "App is running" << endl;
	}

	virtual void finish() {
		cout << endl << YELLOW_FC<< "------------ IESIRE ------------" << DEFAULT_FC << endl;
	};
};

class Calculator : public App {
	Expression currentExp;
	int counter;
	enum actions {
		evaluateExpression = 1,
		saveVariable = 2,
		showVariables = 3,
		processExpressionsFromTxtFile = 4,
		exit = 5
	} currentAction;
	
public:
	Calculator() : App() {
		counter = 0;
		currentAction = evaluateExpression;
	};

	Calculator(string appName) : App(appName) {
		counter = 0;
		currentAction = evaluateExpression;
	};

	void displayMainMenu() {
		int choice = currentAction;
		int numChoices = 5;
		char key = NULL;
		
		// navigation loop runs until user presses enter on the desired option
		while (key != '\r') {
			if(key != NULL) system("cls");
			cout << endl<<RED_FC<< "--------- MENIU --------" <<DEFAULT_FC<< endl;
			
			cout << ((choice==1) ? YELLOW_FC : DEFAULT_FC) << "1. Introducere ecuatie" << endl;
			cout << ((choice == 2) ? YELLOW_FC : DEFAULT_FC)<< "2. Salveaza rezultatul curent intr-o variabila" << endl;
			cout << ((choice == 3) ? YELLOW_FC : DEFAULT_FC) << "3. Afiseaza variabilele salvate" << endl;
			cout << ((choice == 4) ? YELLOW_FC : DEFAULT_FC)<< "4. Citire ecuatii din fisier text" << endl;
			cout << ((choice == 5) ? YELLOW_FC : DEFAULT_FC)<< "5. Iesire" << DEFAULT_FC<< endl;

			cout << endl;

			key = _getch();
			// up arrow key pressed
			if (key == 72) {
				if (choice > 1) choice--;
				else choice = numChoices;
			} 
			// down arrow key pressed
			if (key == 80) {
				if (choice < numChoices) choice++;
				else choice = 1;
			}
		}
		
		currentAction = (actions)choice;
	}

	void finish() {
		cout << endl << YELLOW_FC << "Se iese din aplicatie. Apasati o tasta..." <<DEFAULT_FC<< endl;
		char key = _getch();
	}

	void run() {
		while (currentAction != exit) {
			this->displayMainMenu();
			switch (currentAction) {
			case evaluateExpression: 
				this->processExpressionFromConsole();
				break;
			case saveVariable:
				this->saveResultAsVariable();
				break;
			case showVariables:
				this->showSavedVariables();
				break;
			case processExpressionsFromTxtFile:
				this->processExpressionsFromTextFile();
				break;
			default:
				currentAction = exit;
				break;
			}
			
		}
		
	}

	void processCmdArgs(int numArgs, char**args) {
		// make one expression out of all arguments
		for (int i = 1; i < numArgs; i++) {
			string seq = args[i];
			currentExp.addToInfix(seq);
		}
		// evaluate it
		try {
			currentExp.evaluate();
			cout<< "= " << currentExp << endl;
		}
		catch (exception& e) {
			cout << e.what() << endl;
		}
		cout << endl;
	}

	void processExpressionFromConsole() {
		// TO DO: be able to use variables in expressions
		cout << GREEN_FC << "Introduceti o expresie matematica: " << DEFAULT_FC << endl;
		cin>>ws;

		cin >> currentExp;

		try {
			currentExp.evaluate();
			cout << "= " << currentExp << endl;
		}
		catch (exception& e) {
			cout << e.what() << endl;
		}
		cout << endl;
	}

	void saveResultAsVariable() {
		// TO DO: implement functionality with binary files
		cout << GREEN_FC << "Rezultatul expresiei curente este: " << this->currentExp.getResult() << DEFAULT_FC << endl;
		cout << "Se salveaza..." << endl;
	}

	void showSavedVariables() {
		// TO DO: implement map at class level and read it from there
		map <string, double> storedVariables;
		storedVariables["var"] = 2;
		storedVariables["anotherVariable"] = 7890.0078;
		storedVariables["variable2"] = 222.00678;

		cout << left << GREEN_FC << setw(25) << "Variable" <<  setw(20) << "Value" <<DEFAULT_FC<< endl << endl;
		map<string, double>::iterator iterator;
		for (iterator = storedVariables.begin(); iterator != storedVariables.end(); ++iterator){
			cout <<left<< setw(25) << iterator->first <<  setw(20) << iterator->second << endl;
		}
		cout << endl;
	}

	void processExpressionsFromTextFile() {
		// Ask user for source file
		cout <<GREEN_FC<< "Introduceti fisierul text sursa: "<<DEFAULT_FC;
		string srcFile;
		cin >> srcFile;

		
		ifstream f(srcFile);
		if (!f.is_open()) cout << "Fisierul nu a fost gasit!"<<endl;
		else {

			// Ask user for destination file (console, chosen txt file)
			char key = NULL;
			cout << endl<<"Doriti scrierea rezultatelor intr-un fisier text? (y/n)" << endl;
			while (key != 'y' and key != 'n') {
				key = _getch();
			}

			string destinationFile;
			ofstream g;
			if (key == 'y') {
				cout << GREEN_FC << "Introduceti fisierul text destinatie: " << DEFAULT_FC;
				cin >> destinationFile;
				g.open(destinationFile);
			}
			cout << endl;

			// Get number of expressions, loop through and evaluate them and display result where user wanted
			f >> ws;
			while (!f.eof()) {
				f >> currentExp;
				try {
					currentExp.evaluate();
					if (g.is_open()) g << currentExp << endl;
					else cout << currentExp << endl;
				}
				catch (exception& e) {
					if (g.is_open()) g << e.what() << endl;
					else cout << e.what() << endl;
				}
			}
			if (g.is_open()) {
				cout << YELLOW_FC<<"Rezultatele au fost scrise in fisierul "<<destinationFile <<DEFAULT_FC<< endl;
				g.close();
			}
			f.close();
		}
		
	}

	
};

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

	/*
	//////////////////////////
	// Expression evaluation functionality
	string input = ""; int counter = 0;

	
	cout << YELLOW_FC << "Introduceti o expresie matematica: (pentru iesire introduceti 'exit')" << DEFAULT_FC << endl;
	
	getline(cin, input);

	
	while (input != "exit") {
			Expression expression(++counter, input);

			try {
				expression.evaluate();
				cout << expression << endl;
			}
			catch (exception& e) {
				cout << e.what() << endl;
			}
			cout << endl;
		
		
		getline(cin, input);
	}
	cout << "Expresii evaluate: " << counter << endl;
	*/
	
}