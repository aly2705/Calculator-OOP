#pragma once
#include <string>
using namespace std;


class App
{
protected:
	string appName;
public:
	App();
	App(string appName);

	// Pure virtual methods
	virtual void displayMainMenu() = 0;

	// Virtual methods
	virtual void start();

	virtual void run();

	virtual void finish();
	
};

