#include "NumberStack.h"
#include <iostream>
using namespace std;

/////////////////////////////////////
// Constructors
NumberStack::NumberStack() {
	values = nullptr;
	size = 0;
}

NumberStack::NumberStack(double* values, int size) : NumberStack() {
	if (values != nullptr && size > 0) {
		this->size = size;
		this->values = new double[size];
		for (int i = 0; i < size; i++) {
			this->values[i] = values[i];
		}
	}
}

NumberStack::NumberStack(const NumberStack& s) : NumberStack() {
	if (s.values != nullptr && s.size > 0) {
		size = s.size;
		values = new double[s.size];
		for (int i = 0; i < size; i++) {
			values[i] = s.values[i];
		}
	}
}

/////////////////////////////////////
// Destructor
NumberStack::~NumberStack() {
	if (values != nullptr && size > 0) {
		delete[] values;
		values = nullptr;
	};
}

/////////////////////////////////////
// Operator overloading
NumberStack& NumberStack::operator=(const NumberStack& s) {
	if (this != &s) {

		if (values != nullptr && size > 0) {
			delete[] values;
			values = nullptr;
		};

		if (s.values != nullptr && s.size > 0) {
			size = s.size;
			values = new double[s.size];
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
};

NumberStack NumberStack::operator++() {
	// increments each value with 1
	if (values != nullptr && size>0) {
		for (int i = 0; i < size; i++) {
			values[i]++;
		}
	}
	return *this;
};
NumberStack NumberStack::operator++(int x) {
	// increments each value with 1
	NumberStack copie = *this;
	if (values != nullptr && size > 0) {
		for (int i = 0; i < size; i++) {
			values[i]++;
		}
	}
	return copie;
};

NumberStack NumberStack::operator--() {
	// decrements each value with 1
	if (values != nullptr && size > 0) {
		for (int i = 0; i < size; i++) {
			values[i]--;
		}
	}
	return *this;
};
NumberStack NumberStack::operator--(int x) {
	// decrements each value with 1
	NumberStack copie = *this;
	if (values != nullptr && size > 0) {
		for (int i = 0; i < size; i++) {
			values[i]--;
		}
	}
	return copie;
};

ostream& operator<<(ostream& out, const NumberStack& s) {
	if (s.values != nullptr)
		for (int i = 0; i < s.size; i++) {
			out << s.values[i] << " ";
		}
	else out << "Stiva este goala";
	out << endl;
	return out;
};
istream& operator>>(istream& in, NumberStack& s) {
	int dim;
	
	cout << "Dimensiune stiva de numere: ";
	in >> dim;
	if (dim > 0) {
		double* buffer = new double[dim];
		cout << endl << "Elemente: ";
		for (int i = 0; i < dim; i++)
		{
			in >> buffer[i];
		}
		cout << endl;
		s.setValues(buffer, dim);
	} else throw exception("Dimensiune invalida");
	
	return in;
};

/////////////////////////////////////
// Access methods
int NumberStack::getSize() {
	return size;

}
double NumberStack::getValue(int index) {
	if (index < size) {
		return values[index];
	}
	else return -1;
}

void NumberStack::setValues(double* newValues, int newSize) {
	if (values != nullptr && size > 0) {
		delete[] values;
		values = nullptr;
	};

	if (newValues != nullptr && newSize > 0) {
		size = newSize;
		values = new double[newSize];
		for (int i = 0; i < newSize; i++) {
			values[i] = newValues[i];
		}
	}
	else {
		size = 0;
		values = nullptr;
	}
}

/////////////////////////////////////
// Generic methods
void NumberStack::push(double num) {
	if (values != nullptr && size > 0) {
		double* buffer = new double[size];
		for (int i = 0; i < size; i++) {
			buffer[i] = values[i];
		}
		delete[] values;
		values = new double[size + 1];
		for (int i = 0; i < size; i++) {
			values[i] = buffer[i];
		}
		values[size] = num;
		size = size + 1;
		delete[] buffer;
	}
	else {
		values = new double[1];
		size = 1;
		values[size - 1] = num;
	}
}
double NumberStack::pop() {
	if (values != nullptr && size > 0) {
		double* buffer = new double[size];
		for (int i = 0; i < size; i++) {
			buffer[i] = values[i];
		}
		delete[] values;
		values = new double[size - 1];
		for (int i = 0; i < size - 1; i++) {
			values[i] = buffer[i];
		}
		double poppedValue = buffer[size - 1];
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

