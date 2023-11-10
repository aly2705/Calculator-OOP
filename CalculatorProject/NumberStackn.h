#pragma once

class NumberStack {
private:
	int size;
	float* values;

public:
	/////////////////////////////////////
	// Constructors
	NumberStack();

	NumberStack(float* values, int size);

	NumberStack(const NumberStack& s);

	/////////////////////////////////////
	// Destructor
	~NumberStack();

	/////////////////////////////////////
	// Operator overloading
	NumberStack& operator=(const NumberStack& s);

	/////////////////////////////////////
	// Access methods
	int getSize();

	float getValue(int index);

	void setValues(float* newValues, int newSize);

	/////////////////////////////////////
	// Generic methods
	void push(float token);

	float pop();
};