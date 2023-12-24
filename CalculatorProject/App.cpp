#include <iostream>
#include <string>
#include "App.h"
#define YELLOW_FC "\x1B[33m"
#define DEFAULT_FC "\x1B[0m"

App::App() {
	appName = "APP";
}
App::App(string appName) {
	this->appName = appName;
}
void App::start() {
	cout << endl << YELLOW_FC << "------------ " << appName << " ------------" << DEFAULT_FC << endl;
};
void App::run() {
	cout << "App is running" << endl;
}

void App::finish() {
	cout << endl << YELLOW_FC << "------------ IESIRE ------------" << DEFAULT_FC << endl;
};