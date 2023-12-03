#pragma once
#include <iostream>
using namespace std;

class CharStack {
private:
	int size;
	char* values;

public:
	/////////////////////////////////
	// Constructors
	CharStack();

	CharStack(char* values, int size);

	CharStack(const CharStack& s);
	
	/////////////////////////////////
	// Destructor
	~CharStack();

	////////////////////////////////
	// Operator overloading
	CharStack& operator=(const CharStack& s);

	// gives the element at index i 
	// (used to check the last element in the algorithm to see if it needs to be popped)
	char& operator[](int index);

	// casts the stack into the stack size
	operator int();

	friend ostream& operator<<(ostream& out, const CharStack& s);
	friend istream& operator>>(istream& in, CharStack& s);

	////////////////////////////////
	// Access methods
	int getSize();

	char* getValues();

	void setValues(char* newValues, int newSize);

	/////////////////////////////////
	// Generic methods
	void push(char token);

	char pop();
};