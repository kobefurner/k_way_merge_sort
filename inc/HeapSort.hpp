#ifndef HEAPSORT_HPP
#define HEAPSORT_HPP

template <typename T>
class Heap : public BaseSort<T> {
public:
	Heap(const unsigned int capacity) : BaseSort<T>("Heap", capacity) {};
	void runSort();
private:
	void heapify(unsigned int lastUnsortedIndex, unsigned int parent);
};

template <typename T>
void Heap<T>::heapify(unsigned int lastUnsortedIndex, unsigned int parent) {
	// Find largest among root, left child and right child
	unsigned int largest = parent;
	unsigned int left = 2 * parent + 1;
	unsigned int right = 2 * parent + 2;

	if (left < lastUnsortedIndex && this->arr[left] > this->arr[largest])
		largest = left;

	if (right < lastUnsortedIndex && this->arr[right] > this->arr[largest])
		largest = right;

	// Swap and continue heapifying if root is not largest
	if (largest != parent) {
		T temp = this->arr[parent];
		this->arr[parent] = this->arr[largest];
		this->arr[largest] = temp;
		heapify(lastUnsortedIndex, largest);
	}
}

template <typename T>
void Heap<T>::runSort() {

	// Put tree in max heap (all parents bigger than their children)
	unsigned int  i = this->capacity / 2;
	while (i > 0) {
		i--;
		heapify(this->capacity, i);
	}

	// Swap root to sorted position, re-heap, repeat.
	unsigned int lastUnsortedIndex = this->capacity;
	while (lastUnsortedIndex > 0) {
		lastUnsortedIndex--;
		T temp = this->arr[0];
		this->arr[0] = this->arr[lastUnsortedIndex];
		this->arr[lastUnsortedIndex] = temp;
		heapify(lastUnsortedIndex, 0);
	}
}

#endif
