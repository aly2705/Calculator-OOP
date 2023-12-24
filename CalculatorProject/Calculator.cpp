#define YELLOW_FC "\x1B[33m"
#define DEFAULT_FC "\x1B[0m"
#define GREEN_FC "\x1B[32m"
#define RED_FC "\x1B[31m"
#include <iostream>
#include <string>
#include <string.h>
#include <iomanip>
#include <map>
#include <conio.h>
#include "Calculator.h"
#include "App.h"

Calculator::Calculator() : App() {
	currentAction = evaluateExpression;
};

Calculator::Calculator(string appName) : App(appName) {
	currentAction = evaluateExpression;
};

void Calculator::deserializeVariables() {
	ifstream varFile("Variables.bin", ios::binary);

	if (varFile.is_open()) {
		while (!varFile.eof()) {
			int varNameLength;
			string varName; double result;

			varFile.read((char*)&varNameLength, sizeof(varNameLength));
			if (!varFile.eof()) {
				char* buffer = new char[varNameLength + 1];
				varFile.read(buffer, varNameLength + 1);
				varName = buffer;
				delete[] buffer;

				varFile.read((char*)&result, sizeof(result));

				storedVariables[varName] = result;
			}

		}
		varFile.close();
	}
}

void Calculator::start() {
	cout << endl << YELLOW_FC << "------------ " << appName << " ------------" << DEFAULT_FC << endl;
	this->deserializeVariables();
}

void Calculator::displayMainMenu() {
	int choice = currentAction;
	int numChoices = 5;
	char key = NULL;

	// navigation loop runs until user presses enter on the desired option
	while (key != '\r') {
		if (key != NULL) system("cls");
		cout << endl << RED_FC << "--------- MENIU --------" << DEFAULT_FC << endl;

		cout << ((choice == 1) ? YELLOW_FC : DEFAULT_FC) << "1. Introducere ecuatie" << endl;
		cout << ((choice == 2) ? YELLOW_FC : DEFAULT_FC) << "2. Salveaza rezultatul curent intr-o variabila" << endl;
		cout << ((choice == 3) ? YELLOW_FC : DEFAULT_FC) << "3. Afiseaza variabilele salvate" << endl;
		cout << ((choice == 4) ? YELLOW_FC : DEFAULT_FC) << "4. Citire ecuatii din fisier text" << endl;
		cout << ((choice == 5) ? YELLOW_FC : DEFAULT_FC) << "5. Iesire" << DEFAULT_FC << endl;

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

void Calculator::finish() {
	cout << endl << YELLOW_FC << "Se iese din aplicatie. Apasati o tasta..." << DEFAULT_FC << endl;
	char key = _getch();
}

void Calculator::run() {
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

void Calculator::processCmdArgs(int numArgs, char** args) {
	// make one expression out of all arguments
	for (int i = 1; i < numArgs; i++) {
		string seq = args[i];
		currentExp.addToInfix(seq);
	}
	// evaluate it
	try {
		currentExp.evaluate();
		cout << "= " << currentExp << endl;
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
	cout << endl;
}

void Calculator::processExpressionFromConsole() {
	cout << GREEN_FC << "Introduceti o expresie matematica: " << DEFAULT_FC << endl;
	cin >> ws;

	cin >> currentExp;
	currentExp.replaceVariablesInInfix(storedVariables);

	try {
		currentExp.evaluate();
		cout << "= " << currentExp << endl;
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
	cout << endl;
}

void Calculator::saveResultAsVariable() {
	cout << GREEN_FC << "Rezultatul expresiei curente este: " << this->currentExp.getResult() << DEFAULT_FC << endl;
	cout << "Introduceti numele variabilei (sau 'exit' pentru anularea actiunii): ";

	string varName;
	cin >> varName;

	if (varName != "exit") {

		// Validations
		bool isAvailable = (storedVariables.find(varName) == storedVariables.end());
		while (isdigit(varName[0]) || !isAvailable) {
			if (!isAvailable) cout << "Numele variabilei exista deja! Incercati din nou!" << endl;
			else cout << "Numele variabilei nu poate incepe cu o cifra! Incercati din nou." << endl;

			cin >> varName;
			isAvailable = (storedVariables.find(varName) == storedVariables.end());

			if (varName == "exit") return;
		}

		ofstream varFile("Variables.bin", ios::binary | ios::app);

		int varNameLength = varName.length();
		double result = this->currentExp.getResult();
		varFile.write((char*)&varNameLength, sizeof(varNameLength));
		varFile.write(varName.c_str(), varNameLength + 1);
		varFile.write((char*)&result, sizeof(result));

		varFile.close();
		storedVariables[varName] = this->currentExp.getResult();
		cout << "Variabila salvata!" << endl;
	}
}

void Calculator::showSavedVariables() {

	if (storedVariables.begin() != storedVariables.end()) {
		cout << left << GREEN_FC << setw(25) << "Variable" << setw(20) << "Value" << DEFAULT_FC << endl << endl;
		map<string, double>::iterator iterator;
		for (iterator = storedVariables.begin(); iterator != storedVariables.end(); ++iterator) {
			cout << left << setw(25) << iterator->first << setw(20) << iterator->second << endl;
		}
	}
	else cout << "Nu exista variabile salvate" << endl;

	cout << endl;
}

void Calculator::processExpressionsFromTextFile() {
	// Ask user for source file
	cout << GREEN_FC << "Introduceti fisierul text sursa: " << DEFAULT_FC;
	string srcFile;
	cin >> srcFile;


	ifstream f(srcFile);
	if (!f.is_open()) cout << "Fisierul nu a fost gasit!" << endl;
	else {

		// Ask user for destination file (console, chosen txt file)
		char key = NULL;
		cout << endl << "Doriti scrierea rezultatelor intr-un fisier text? (y/n)" << endl;
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
			currentExp.replaceVariablesInInfix(storedVariables);

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
			cout << YELLOW_FC << "Rezultatele au fost scrise in fisierul " << destinationFile << DEFAULT_FC << endl;
			g.close();
		}
		f.close();
	}

}
