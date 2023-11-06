#pragma once

class NumberStack {
private:
	int size;
	float* values;

public:
	NumberStack();

	NumberStack(const NumberStack& s);

	~NumberStack();

	NumberStack& operator=(const NumberStack& s);

	void push(float token);

	float pop();

	int getSize();

	float getValue(int index);
};