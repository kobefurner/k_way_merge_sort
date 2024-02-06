#ifndef BASESORT_H
#define BASESORT_H

#include <iostream>
#include <string>
#include <random>

using std::string;

using std::cout;
using std::endl;

template <typename T>
class BaseSort {
public:
	BaseSort(const string& sortName, const unsigned int capacity);
	
	// Rule of 5, keep destructor, disable copy and move semantics
	~BaseSort();
	BaseSort(const BaseSort& obj) = delete;
	BaseSort& operator=(const BaseSort& obj) = delete;
	BaseSort(BaseSort&& obj) = delete;
	BaseSort& operator=(BaseSort&& object) = delete;

	string getName() { return sortName; }
	unsigned int getTotalItems() { return capacity; }
	void loadRandomValues();
	void loadValues(const std::initializer_list<T>& initList);
	void printValues() const;
	bool verifySort() const;

	virtual void runSort() = 0; // Pure virtual function.  
	// It makes the class **abstract**.  In other words,
	// nothing can instantiate an object of this class.  
protected:
	string sortName;
	T* arr{ nullptr };
	unsigned int capacity{ 0 };
private:

};

template <typename T>
BaseSort<T>::BaseSort(const string& sortName, const unsigned int capacity) {
	this->sortName = sortName;
	this->capacity = capacity;
	this->arr = new T[capacity];
}
template <typename T>
BaseSort<T>::~BaseSort() {
	delete[] arr;
}

template <typename T>
void BaseSort<T>::loadRandomValues() {
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<unsigned int> distrib(0, 0xffffffffu);

	for (unsigned int i = 0; i < capacity; ++i) {
		this->arr[i] = distrib(gen);
	}
}

template <typename T>
void BaseSort<T>::loadValues(const std::initializer_list<T>& initList) {
	std::copy(initList.begin(), initList.end(), this->arr);
}

template <>
void BaseSort<double>::loadRandomValues() {
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<double> distrib(0, 1);

	for (unsigned int i = 0; i < capacity; ++i) {
		this->arr[i] = distrib(gen);
	}
}

template <>
void BaseSort<string>::loadRandomValues() {
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(0); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<unsigned int> distrib{ 'a','z' };

	string str(4,'\0');
	for (unsigned int i = 0; i < capacity; ++i) {
		for (auto& letter : str) {
			letter = distrib(gen);
		}
		this->arr[i] = str;
	}	
}

template <typename T>
void BaseSort<T>::printValues() const {
	if (capacity < 50) {
		for (unsigned int i = 0; i < capacity; i++) {
			cout << arr[i] << " ";
		}
		cout << endl;
	}
}

template <typename T>
bool BaseSort<T>::verifySort() const {
	for (unsigned int i = 0; i < capacity - 1; i++) {
		if (arr[i + 1] < arr[i]) {
			cout << "Not sorted at index: " << (i + 1) << endl;
			return false;
		}
	}
	cout << "Sorted!" << endl;
	return true;
}

#endif
