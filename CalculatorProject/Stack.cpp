#include "Stack.h"
#include <iostream>
using namespace std;

/////////////////////////////////////
// Constructors
template <typename T>
Stack<T>::Stack() {
	values = nullptr;
	size = 0;
}

template <typename T>
Stack<T>::Stack(T* values, int size) : Stack() {
	if (values != nullptr && size > 0) {
		this->size = size;
		this->values = new T[size];
		for (int i = 0; i < size; i++) {
			this->values[i] = values[i];
		}
	}
}

template <typename T>
Stack<T>::Stack(const Stack& s) : Stack() {
	if (s.values != nullptr && s.size > 0) {
		size = s.size;
		values = new T[s.size];
		for (int i = 0; i < size; i++) {
			values[i] = s.values[i];
		}
	}
}

/////////////////////////////////////
// Destructor
template <typename T>
Stack<T>::~Stack() {
	if (values != nullptr && size > 0) {
		delete[] values;
		values = nullptr;
	};
}

/////////////////////////////////////
// Operator overloading
template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& s) {
	if (this != &s) {

		if (values != nullptr && size > 0) {
			delete[] values;
			values = nullptr;
		};

		if (s.values != nullptr && s.size > 0) {
			size = s.size;
			values = new T[s.size];
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


template <typename T>
T& Stack<T>::operator[](int index) {
	if (values != nullptr)
		if (index >= 0 && index < size) {
			return values[index];
		}
		else throw exception("Index invalid");
	else throw exception("Stiva este goala");
}

template <typename T>
Stack<T>::operator int() {
	return size;
}

template <typename T>
ostream& operator<<(ostream& out, const Stack<T>& s) {
	if (s.values != nullptr)
		for (int i = 0; i < s.size; i++) {
			out << s.values[i] << " ";
		}
	else out << "Stiva este goala";
	out << endl;
	return out;
};

template <typename T>
istream& operator>>(istream& in, Stack<T>& s) {
	int dim;

	cout << "Dimensiune stiva: ";
	in >> dim;
	if (dim > 0) {
		T* buffer = new T[dim];
		cout << endl << "Elemente: ";
		for (int i = 0; i < dim; i++)
		{
			in >> buffer[i];
		}
		cout << endl;
		s.setValues(buffer, dim);
	}
	else throw exception("Dimensiune invalida");

	return in;
};

/////////////////////////////////////
// Access methods
template <typename T>
int Stack<T>::getSize() {
	return size;

}

template <typename T>
T* Stack<T>::getValues() {
	T* copy = nullptr;
	if (values != nullptr) {
		copy = new T[size];
		for (int i = 0; i < size; i++) {
			copy[i] = values[i];
		}
	}
	return copy;
}

template <typename T>
void Stack<T>::setValues(T* newValues, int newSize) {
	if (values != nullptr && size > 0) {
		delete[] values;
		values = nullptr;
	};

	if (newValues != nullptr && newSize > 0) {
		size = newSize;
		values = new T[newSize];
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
template <typename T>
void Stack<T>::push(T num) {
	if (values != nullptr && size > 0) {
		T* buffer = new T[size];
		for (int i = 0; i < size; i++) {
			buffer[i] = values[i];
		}
		delete[] values;
		values = new T[size + 1];
		for (int i = 0; i < size; i++) {
			values[i] = buffer[i];
		}
		values[size] = num;
		size = size + 1;
		delete[] buffer;
	}
	else {
		values = new T[1];
		size = 1;
		values[size - 1] = num;
	}
}

template <typename T>
T Stack<T>::pop() {
	if (values != nullptr && size > 0) {
		T* buffer = new T[size];
		for (int i = 0; i < size; i++) {
			buffer[i] = values[i];
		}
		delete[] values;
		values = new T[size - 1];
		for (int i = 0; i < size - 1; i++) {
			values[i] = buffer[i];
		}
		T poppedValue = buffer[size - 1];
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

template <typename T>
T Stack<T>::top() {
	return values[size - 1];
}