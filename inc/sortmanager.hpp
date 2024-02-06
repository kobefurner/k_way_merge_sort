#include "BaseSort.hpp"
#include "BubbleSort.hpp"
#include "SelectionSort.hpp"
#include "InsertionSort.hpp"
#include "QuickSort.hpp"
#include "HeapSort.hpp"
#include "MergeSort.hpp"
#include "ArrayKMergeSort.hpp"
#include "HeapKMergeSort.hpp"
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <chrono>

using std::cout;
using std::cin;
using std::endl;
using std::string;



template <typename T>
double runMySort(BaseSort<T>&& sortObj) {
	cout << "Running sort: " << sortObj.getName() << " with " << sortObj.getTotalItems() << " items" << endl;
	sortObj.loadRandomValues();
	sortObj.printValues();
	auto t1 = std::chrono::high_resolution_clock::now();
	sortObj.runSort();
	auto t2 = std::chrono::high_resolution_clock::now();

	sortObj.printValues();
	bool sortResult = sortObj.verifySort();
	double timeToSort = 0.0;
	if (sortResult) {
		std::chrono::duration<double, std::milli> fp_ms = t2 - t1;
		timeToSort = fp_ms.count();
		std::cout << "Sort completed in " << fp_ms.count() << " milliseconds" << endl;
	}
	else {
		timeToSort = -1.0; // Negative indicates failed sort
	}
	return timeToSort;
}

template <typename T>
double runMySort(BaseSort<T>&& sortObj, std::initializer_list<T> initList) {
	cout << "Running sort: " << sortObj.getName() << " with " << sortObj.getTotalItems() << " items" << endl;
	sortObj.loadValues(initList);
	sortObj.printValues();
	auto t1 = std::chrono::high_resolution_clock::now();
	sortObj.runSort();
	auto t2 = std::chrono::high_resolution_clock::now();

	sortObj.printValues();
	bool sortResult = sortObj.verifySort();
	double timeToSort = 0.0;
	if (sortResult) {
		std::chrono::duration<double, std::milli> fp_ms = t2 - t1;
		timeToSort = fp_ms.count();
		std::cout << "Sort completed in " << fp_ms.count() << " milliseconds" << endl;
	}
	else {
		timeToSort = -1.0; // Negative indicates failed sort
	}
	return timeToSort;
}
