#ifndef BUBBLESORT_HPP
#define BUBBLESORT_HPP

#include "BaseSort.hpp"

template <typename T>
class Bubble : public BaseSort <T> {
public:
	Bubble(const unsigned int capacity) : BaseSort<T>("Bubble", capacity) {}
	void runSort();
private:
};

template <typename T>
void Bubble<T>::runSort() {
	for (unsigned int round = 0; round < this->capacity - 1; round++) {
		for (unsigned int i = 0; i < this->capacity - 1 - round; i++) {
			if (this->arr[i + 1] < this->arr[i]) {
				T temp = this->arr[i];
				this->arr[i] = this->arr[i + 1];
				this->arr[i + 1] = temp;
			}
		}
	}
}
#endif
