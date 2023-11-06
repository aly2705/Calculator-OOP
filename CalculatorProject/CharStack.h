#pragma once

class CharStack {
private:
	int size;
	char* values;

public:
	CharStack();

	CharStack(const CharStack& s);
	
	~CharStack();

	CharStack& operator=(const CharStack& s);

	void push(char token);

	char pop();

	int getSize();

	char getValue(int index);
};