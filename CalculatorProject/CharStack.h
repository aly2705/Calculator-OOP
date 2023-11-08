#pragma once

class CharStack {
private:
	int size;
	char* values;

public:
	// Constructors
	CharStack();

	CharStack(char* values, int size);

	CharStack(const CharStack& s);
	
	// Destructor
	~CharStack();

	// Operator overloading
	CharStack& operator=(const CharStack& s);

	// Access methods
	int getSize();

	char getValue(int index);

	void setValues(char* newValues, int newSize);

	// Generic methods
	void push(char token);

	char pop();
};