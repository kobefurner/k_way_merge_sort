#ifndef HEAPKMERGESORT_HPP
#define HEAPKMERGESORT_HPP
#include <algorithm>

template <typename T>
struct heapAddresses{
	T* subArrayCurrent; // Make this a stack array for performance. This holds all pointers to existing array values for pointer arithmetic
	T* subArrayEnd;
};
template <typename T, unsigned int K>
class MinHeap {
public:
	MinHeap(T* sourceArray, unsigned int sourceArraySize, int firstIndex, int lastIndexes[K]);
	T getSmallest();
private:
	void addSubArray(T* subArrayStart, T* subArrayEnd);
	heapAddresses<T> heap[K];
	int firstIndex;
	int lastIndexes[K];
	unsigned int size{ 0 };
	T* sourceArray{ nullptr };
	unsigned int sourceArraySize{ 0 };
};

template <typename T, unsigned int K>
MinHeap<T, K>::MinHeap(T* sourceArray, unsigned int sourceArraySize, int firstIndex,  int lastIndexes[K]) {
    this->sourceArray = sourceArray;
    this->sourceArraySize = sourceArraySize;

    if ( lastIndexes[0] - firstIndex ) {
       this->addSubArray(sourceArray, sourceArray + lastIndexes[0] - firstIndex);
	}
	int i = 1;
	while ( i < K) {
      if ( lastIndexes[i] - lastIndexes[i-1] ) {
		this->addSubArray(sourceArray + lastIndexes[i-1] - firstIndex, sourceArray + lastIndexes[i] - firstIndex );
	  }
	  this->lastIndexes[i] = lastIndexes[i];
	  i++;
	}
}

template <typename T, unsigned int K>
void MinHeap<T, K>::addSubArray(T* subArrayStart, T* subArrayEnd) {

	unsigned int currIndex = size;
	heap[size].subArrayCurrent = subArrayStart;
	heap[size].subArrayEnd = subArrayEnd;
	size++;

	// Work upward. Ensure the array starting with the lowest value ends up at the top of the heap tree.
	while (currIndex > 0 && *heap[currIndex].subArrayCurrent < *heap[(currIndex - 1) / 2].subArrayCurrent) {
		//swap
		auto temp = heap[currIndex];
		heap[currIndex] = heap[(currIndex - 1) / 2];
		heap[(currIndex - 1) / 2] = temp;
		currIndex = (currIndex - 1) / 2;
	}
}

template <typename T, unsigned int K>
T MinHeap<T, K>::getSmallest() {

	// Get top, replace it with the last item to keep the tree balanced
	T retVal = *heap[0].subArrayCurrent;

	// See if this subarray has more values or not.  
	//if (((int(heap[0] - sourceArray) + 2) * K - 1) % sourceArraySize >= K) {
	if (heap[0].subArrayCurrent < heap[0].subArrayEnd - 1) {
		// We're still within a subarray, use the next value of the subarray
		heap[0].subArrayCurrent = heap[0].subArrayCurrent + 1;
	}
	else {
		// This sub array is done.  Put the last leaf of the heap at root
		heap[0] = heap[size - 1];
		size--;
	}

	// Work downward
	unsigned int parent = 0;
	do {
		unsigned int left = 2 * parent + 1;
		unsigned int right = 2 * parent + 2;
		if (left >= size) {
			return retVal;
		}
		if (right < size) {
			if (*heap[left].subArrayCurrent < *heap[parent].subArrayCurrent) {
				if (*heap[right].subArrayCurrent < *heap[left].subArrayCurrent) {
					auto temp = heap[parent];
					heap[parent] = heap[right];
					heap[right] = temp;
					parent = right;
				}
				else {
					auto temp = heap[parent];
					heap[parent] = heap[left];
					heap[left] = temp;
					parent = left;
				}
			}
			else if (*heap[right].subArrayCurrent < *heap[parent].subArrayCurrent) {
				auto temp = heap[parent];
				heap[parent] = heap[right];
				heap[right] = temp;
				parent = right;
			}
			else {
				return retVal;
			}
		}
		else {
			if (*heap[left].subArrayCurrent < *heap[parent].subArrayCurrent) {
				auto temp = heap[parent];
				heap[parent] = heap[left];
				heap[left] = temp;
			}
			return retVal;
		}
	} while (true);

}


// TODO: Your homework assignment code goes here

template <typename T, unsigned int K>
class HeapKMerge : public BaseSort<T> {
	public:
		HeapKMerge(const unsigned int capacity) : BaseSort<T>("Heap - K-Way Merge", capacity) {}
		void runSort();
	private:
	void runSort(unsigned int firstIndex, unsigned int lastIndex);
};

template <typename T, unsigned int K>
void HeapKMerge<T, K>::runSort() {
	runSort(0, this->capacity);
}

template <typename T, unsigned int K>
void HeapKMerge<T, K>::runSort(unsigned int firstIndex, unsigned int lastIndex) {
	unsigned int number_of_array_values = lastIndex - firstIndex;
	 if (number_of_array_values < 2) {
		return; 
	}

    int subarray_size = number_of_array_values / K;
	int remainder = number_of_array_values % K;
	int lastIndexesArray[K];

	for (int i = 0; i < K; i++) {
		int first = firstIndex + i * subarray_size + std::min(i, remainder);
		int last = first + subarray_size + (i < remainder ? 1 : 0);
		runSort(first, last);
		lastIndexesArray[i] = last;
	}

	T* arrayCopy = new T[number_of_array_values];
	for (int i = 0; i < number_of_array_values; i++) {
		arrayCopy[i] = this->arr[firstIndex + i];
	}

	MinHeap<T, K> minHeap(arrayCopy, number_of_array_values, firstIndex, lastIndexesArray);
	for (int i = 0; i < number_of_array_values; i++) {
		this->arr[firstIndex + i] = minHeap.getSmallest();
	}

	delete[] arrayCopy;
}

#endif