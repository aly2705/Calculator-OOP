#pragma once
#include <string>
#include <map>
#include "Expression.h";
#include "App.h";

class Calculator : public App {
private:
	Expression currentExp;
	map <string, double> storedVariables;
	enum actions {
		evaluateExpression = 1,
		saveVariable = 2,
		showVariables = 3,
		processExpressionsFromTxtFile = 4,
		exit = 5
	} currentAction;

public:
	Calculator();

	Calculator(string appName);

	void start();

	void displayMainMenu();

	void deserializeVariables();

	void run();

	void finish();

	void processCmdArgs(int numArgs, char** args);

	void processExpressionFromConsole();

	void saveResultAsVariable();

	void showSavedVariables();

	void processExpressionsFromTextFile();
};

