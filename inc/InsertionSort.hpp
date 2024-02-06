#ifndef INSERTIONSORT_HPP
#define INSERTIONSORT_HPP
template <typename T>
class Insertion : public BaseSort<T> {
public:
	Insertion(const unsigned int capacity) : BaseSort<T>("Insertion", capacity) {};
	void runSort();
private:
};

template <typename T>
void Insertion<T>::runSort() {
	// The outer loop's job is to...
	// Obtain the leftmost unsorted value, iterates one index to the right each round.  Starts at 1
	for (unsigned int i = 1; i < this->capacity; i++) {
		// The inner loop's job is to...  
		// Take the leftmost unsorted value, walk to the left (back to index 0), swapping along the way until
		// no swaps are needed, or until we get to index 0.      
		unsigned int j = i;
		while (j > 0 && this->arr[j] < this->arr[j - 1]) {
			T temp = this->arr[j];
			this->arr[j] = this->arr[j - 1];
			this->arr[j - 1] = temp;
			j--;
		}
	}
}

#endif
