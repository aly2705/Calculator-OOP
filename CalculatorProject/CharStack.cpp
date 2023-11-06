#include "CharStack.h";


CharStack::CharStack() {
	values = nullptr;
	size = 0;
}

CharStack::CharStack(const CharStack& s) : CharStack() {
	if (s.values != nullptr && s.size > 0) {
		size = s.size;
		values = new char[s.size];
		for (int i = 0; i < size; i++) {
			values[i] = s.values[i];
		}
	}
}
CharStack::~CharStack() {
	if (values != nullptr && size > 0) {
		delete[] values;
		values = nullptr;
	};
}
CharStack& CharStack::operator=(const CharStack& s) {
	if (this != &s) {

		if (values != nullptr && size > 0) {
			delete[] values;
			values = nullptr;
		};

		if (s.values != nullptr && s.size > 0) {
			size = s.size;
			values = new char[s.size];
			for (int i = 0; i < size; i++) {
				values[i] = s.values[i];
			}
		}
		else {
			size = 0;
			values = nullptr;
		}
	}
	return *this;
}
void CharStack::push(char token) {
	if (values != nullptr && size > 0) {
		char* buffer = new char[size];
		for (int i = 0; i < size; i++) {
			buffer[i] = values[i];
		}
		delete[] values;
		values = new char[size + 1];
		for (int i = 0; i < size; i++) {
			values[i] = buffer[i];
		}
		values[size] = token;
		size = size + 1;
		delete[] buffer;
	}
	else {
		values = new char[1];
		size = 1;
		values[size - 1] = token;
	}
}
char CharStack::pop() {
	if (values != nullptr && size > 0) {
		char* buffer = new char[size];
		for (int i = 0; i < size; i++) {
			buffer[i] = values[i];
		}
		delete[] values;
		values = new char[size - 1];
		for (int i = 0; i < size - 1; i++) {
			values[i] = buffer[i];
		}
		char poppedValue = buffer[size - 1];
		size = size - 1;
		if (size == 0) {
			values = nullptr;
		}
		delete[] buffer;
		return poppedValue;

	}
	else {
		return -1;
	}
}

int CharStack::getSize() {
	return size;

}
char CharStack::getValue(int index) {
	if (index < size) {
		return values[index];
	}
	else return -1;
}
