#include "BHeap.cpp"
#include <vector>
#include <iostream>
#include <cstdlib>

int main() {
	BinaryHeap<int> * theHeap;
	std::vector<int> items (100);
	std::vector<int>::iterator st = items.begin();

	while (st != items.end()) {
		*st = rand()%200;
		st++;
	}
	
	theHeap = new BinaryHeap<int>(items);

	while(true) {
		int o;
		try {
			theHeap->deleteMin(o);
			std::cout << o << ", ";
		} catch (HeapException ex) {
			std::cout << std::endl;
			break;
		}

	}
}
