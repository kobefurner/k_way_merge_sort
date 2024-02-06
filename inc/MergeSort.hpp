#ifndef MERGESORT_HPP
#define MERGESORT_HPP

template <typename T>
class Merge : public BaseSort<T> {
public:
	Merge(const unsigned int capacity) : BaseSort<T>("Merge", capacity) {}
	void runSort();
private:
	void runSort(unsigned int firstIndex, unsigned int lastIndex);
};


template <typename T>
void Merge<T>::runSort() {
	runSort(0, this->capacity);
}

template <typename T>
void Merge<T>::runSort(unsigned int firstIndex, unsigned int lastIndex) {
	if (lastIndex - firstIndex < 2) {
		return;
	}

	// Find a middle
	unsigned int middleIndex = (lastIndex - firstIndex) / 2 + firstIndex;

	runSort(firstIndex, middleIndex);
	runSort(middleIndex, lastIndex);

	unsigned int leftHalfSize = middleIndex - firstIndex;
	T* leftArray = new T[leftHalfSize];
	for (unsigned int i = 0; i < leftHalfSize; i++) {
		leftArray[i] = this->arr[firstIndex + i];
	}
	unsigned int rightHalfSize = lastIndex - middleIndex;
	T* rightArray = new T[rightHalfSize];
	for (unsigned int i = 0; i < rightHalfSize; i++) {
		rightArray[i] = this->arr[middleIndex + i];
	}
	unsigned int leftIndex = 0;
	unsigned int rightIndex = 0;
	unsigned int arrIndex = firstIndex;

	while (leftIndex < leftHalfSize && rightIndex < rightHalfSize) {
		if (leftArray[leftIndex] <= rightArray[rightIndex]) {
			this->arr[arrIndex] = leftArray[leftIndex];
			leftIndex++;
		}
		else {
			this->arr[arrIndex] = rightArray[rightIndex];
			rightIndex++;
		}
		arrIndex++;
	}
	while (leftIndex < leftHalfSize) {
		this->arr[arrIndex] = leftArray[leftIndex];
		leftIndex++;
		arrIndex++;
	}
	while (rightIndex < rightHalfSize) {
		this->arr[arrIndex] = rightArray[rightIndex];
		rightIndex++;
		arrIndex++;
	}
	delete[] leftArray;
	delete[] rightArray;

}

#endif