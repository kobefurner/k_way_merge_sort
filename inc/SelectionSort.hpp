#ifndef SELECTIONSORT_HPP
#define SELECTIONSORT_HPP

template <typename T>
class Selection : public BaseSort<T> {
public:
	Selection(const unsigned int capacity) : BaseSort<T>("Selection", capacity) {};
	void runSort();
private:
};

template <typename T>
void Selection<T>::runSort() {
	// The outer loop's job is to...
	// Each time the outer loop iterators, it works with the leftmost/unsorted index value
	for (unsigned int i = 0; i < this->capacity - 1; i++) {
		// The inner loop's job is to...  
		// Compare the current index to the rest of the unsorted region
		for (unsigned int j = i + 1; j < this->capacity; j++) {
			// We have an i (the index we hope to sort) and a j (a candidate to check)
			if (this->arr[j] < this->arr[i]) {
				T temp = this->arr[i];
				this->arr[i] = this->arr[j];
				this->arr[j] = temp;
			}
		}
	}
}
#endif
