#include "Set.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

int main() {
	int rng;
	
	Set<int> * s = new Set<int>();
	Set<int> * s2 = new Set<int>();
	srand(time(NULL));
	
	for (int i=0; i<10; i++){
		rng = (rand() % 100);
		s->insert(rng);
	}
	
	List<int>::const_iterator itr = s->begin();
	std::cout << "Set 1: ";
	while (itr != s->end()) {
		std::cout << *itr++ << ", ";
	}	
	std::cout << endl;

	for (int i=0; i<10; i++){
		rng = (rand() % 100);
		s2->insert(rng);
	}
	
	List<int>::const_iterator itr2 = s2->begin();
	std::cout << "Set 2: ";
	while (itr2 != s2->end()) {
		std::cout << *itr2++ << ", ";
	}	
	std::cout << endl;
	
	Set<int> test = s->set_union(s2);
	Set<int> test2 = s->set_intersect(s2);
	
	List<int>::const_iterator titr = test.begin();
	std::cout << "Test Union: ";
	while (titr != test.end()) {
		std::cout << *titr++ << ", ";
	}	
	std::cout << endl;	
	
	titr = test2.begin();
	std::cout << "Test Intersect: ";
	while (titr != test2.end()) {
		std::cout << *titr++ << ", ";
	}	
	std::cout << endl;	
}
