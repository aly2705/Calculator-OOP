#include "NumberStack.h"

NumberStack::NumberStack() {
	values = nullptr;
	size = 0;
}

NumberStack::NumberStack(const NumberStack& s) : NumberStack() {
	if (s.values != nullptr && s.size > 0) {
		size = s.size;
		values = new float[s.size];
		for (int i = 0; i < size; i++) {
			values[i] = s.values[i];
		}
	}
}
NumberStack::~NumberStack() {
	if (values != nullptr && size > 0) {
		delete[] values;
		values = nullptr;
	};
}
NumberStack& NumberStack::operator=(const NumberStack& s) {
	if (this != &s) {

		if (values != nullptr && size > 0) {
			delete[] values;
			values = nullptr;
		};

		if (s.values != nullptr && s.size > 0) {
			size = s.size;
			values = new float[s.size];
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
void NumberStack::push(float token) {
	if (values != nullptr && size > 0) {
		float* buffer = new float[size];
		for (int i = 0; i < size; i++) {
			buffer[i] = values[i];
		}
		delete[] values;
		values = new float[size + 1];
		for (int i = 0; i < size; i++) {
			values[i] = buffer[i];
		}
		values[size] = token;
		size = size + 1;
		delete[] buffer;
	}
	else {
		values = new float[1];
		size = 1;
		values[size - 1] = token;
	}
}
float NumberStack::pop() {
	if (values != nullptr && size > 0) {
		float* buffer = new float[size];
		for (int i = 0; i < size; i++) {
			buffer[i] = values[i];
		}
		delete[] values;
		values = new float[size - 1];
		for (int i = 0; i < size - 1; i++) {
			values[i] = buffer[i];
		}
		float poppedValue = buffer[size - 1];
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
int NumberStack::getSize() {
	return size;

}
float NumberStack::getValue(int index) {
	if (index < size) {
		return values[index];
	}
	else return -1;
}