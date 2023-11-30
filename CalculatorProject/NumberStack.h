#pragma once
#include <iostream>
using namespace std;


class NumberStack {
private:
	int size;
	double* values;

public:
	/////////////////////////////////////
	// Constructors
	NumberStack();

	NumberStack(double* values, int size);

	NumberStack(const NumberStack& s);

	/////////////////////////////////////
	// Destructor
	~NumberStack();

	/////////////////////////////////////
	// Operator overloading
	NumberStack& operator=(const NumberStack& s);

	NumberStack operator++();
	NumberStack operator++(int x);

	NumberStack operator--();
	NumberStack operator--(int x);


	friend ostream& operator<<(ostream& out, const NumberStack& s);
	friend istream& operator>>(istream& in, NumberStack& s);

	/////////////////////////////////////
	// Access methods
	int getSize();

	double getValue(int index);

	void setValues(double* newValues, int newSize);

	/////////////////////////////////////
	// Generic methods
	void push(double num);

	double pop();
};