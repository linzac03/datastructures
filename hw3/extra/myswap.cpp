#include <iostream>
#include <SinglyList.h>

template <typename Object>
void myswap(Object * el, Object * elem) {
	Object * tmp = el;
	el = elem;
	elem = tmp;
}

int main() {
	std::list<int> myints;
	std::list<int>::iterator start;
	std::list<int>::iterator stop;
	std::list<int>::iterator itr;
	myints.push_back(1);
	myints.push_back(2);
	myints.push_back(3);
	myints.push_back(4);
	start = myints.begin();
	stop = myints.end();
	myswap(&start, &stop);
	for(itr=start; itr != myints.end(); itr++){
		std::cout << *itr << " "; 
	}
	std::cout << std::endl;	
}
