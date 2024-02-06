#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

template <typename T>
class Quick : public BaseSort<T> {
public:
	Quick(const unsigned int capacity) : BaseSort<T>("Quick", capacity) {};
	void runSort();
private:
	void runSort(unsigned int first, unsigned int last);
	unsigned int quickSortPartition(unsigned int first, unsigned int last);
};

template <typename T>
void Quick<T>::runSort() {
	runSort(0, this->capacity);
}

template <typename T>
void Quick<T>::runSort(unsigned int first, unsigned int last) {
	if (first < last) {
		// Obtain a pivot, move all values smaller to the left of pivot
		// and all values larger to the right of pivot
		unsigned int pivotLocation = quickSortPartition(first, last);
		runSort(first, pivotLocation);
		runSort(pivotLocation + 1, last);
	}
}


template <typename T>
unsigned int Quick<T>::quickSortPartition(unsigned int first, unsigned int last) {
	T pivot;
	unsigned int index;
	unsigned int smallIndex;
	T temp;
	pivot = this->arr[first];
	smallIndex = first;
	for (index = first + 1; index < last; index++) {
		if (this->arr[index] < pivot) {
			smallIndex++;
			//swap
			temp = this->arr[smallIndex];
			this->arr[smallIndex] = this->arr[index];
			this->arr[index] = temp;
		}
	}
	// swap pivot into its final spot
	temp = this->arr[first];
	this->arr[first] = this->arr[smallIndex];
	this->arr[smallIndex] = temp;

	return smallIndex;
}

#endif
