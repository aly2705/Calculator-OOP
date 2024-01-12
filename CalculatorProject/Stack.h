#pragma once
#include <iostream>
using namespace std;

template <typename T>
class Stack {
private:
	int size;
	T* values;

public:
	/////////////////////////////////////
	// Constructors
	Stack();

	Stack(T* values, int size);

	Stack(const Stack& s);

	/////////////////////////////////////
	// Destructor
	~Stack();

	/////////////////////////////////////
	// Operator overloading
	Stack& operator=(const Stack& s);

	// gives the element at index i 
	// (used to check the last element in the algorithm to see if it needs to be popped)
	T& operator[](int index);

	// casts the stack into the stack size
	operator int();


	friend ostream& operator<<(ostream& out, const Stack& s);
	friend istream& operator>>(istream& in, Stack& s);

	/////////////////////////////////////
	// Access methods
	int getSize();

	T* getValues();

	void setValues(T* newValues, int newSize);

	/////////////////////////////////////
	// Generic methods
	void push(T num);

	T pop();

	T top();
};
