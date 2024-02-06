#ifndef ARRAYKMERGESORT_HPP
#define ARRAYKMERGESORT_HPP

template <typename T, unsigned int K>
class ArrayKMerge : public BaseSort<T> {
public:
	ArrayKMerge(const unsigned int capacity) : BaseSort<T>("Array K-Way Merge", capacity) {}
	void runSort();
private:
	void runSort(unsigned int firstIndex, unsigned int lastIndex);
};

template <typename T, unsigned int  K>
void ArrayKMerge<T, K>::runSort() {
	runSort(0, this->capacity);
}

struct KIndexes {
	unsigned int kthStartIndex{ 0 };
	unsigned int kthCurrentIndex{ 0 };
	unsigned int kthEndIndex{ 0 };
};

template <typename T, unsigned int K>
void ArrayKMerge<T, K>::runSort(unsigned int firstIndex, unsigned int lastIndex) {

	if (lastIndex - firstIndex < 2) {
		return;
	}

	unsigned int numValues = lastIndex - firstIndex;
	KIndexes indexes[K];
	T* arrayCopy = new T[numValues];

	for (unsigned int i = 0; i < K; i++) {
		indexes[i].kthStartIndex = numValues * i / K;
		indexes[i].kthEndIndex = numValues * (i + 1) / K;
		runSort(firstIndex + indexes[i].kthStartIndex, firstIndex + indexes[i].kthEndIndex);
	}
	for (unsigned int i = 0; i < numValues; i++) {
		arrayCopy[i] = this->arr[firstIndex + i];
	}
	for (unsigned int i = 0; i < K; i++) {
		indexes[i].kthCurrentIndex = indexes[i].kthStartIndex;
	}

	unsigned int itemsSorted = 0;

	while (itemsSorted < numValues) {
		// Scan across all arrays looking for the smallest
		int arrayWithSmallestValue = -1;
		for (unsigned int i = 0; i < K; i++) {
			if (indexes[i].kthCurrentIndex < indexes[i].kthEndIndex) {
				if (arrayWithSmallestValue == -1) {
					arrayWithSmallestValue = i;
				}
				else if (arrayCopy[indexes[i].kthCurrentIndex] < arrayCopy[indexes[arrayWithSmallestValue].kthCurrentIndex]) {
					arrayWithSmallestValue = i;
				}
			}
		}
		// We've found the smallest, move it in
		this->arr[firstIndex + itemsSorted] = arrayCopy[indexes[arrayWithSmallestValue].kthCurrentIndex];
		indexes[arrayWithSmallestValue].kthCurrentIndex++;
		itemsSorted++;
	}
	delete[] arrayCopy;

}

#endif