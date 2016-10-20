#include <list>
#include <iostream>

using namespace std;

template <typename Object>
list<Object> myintersect(list<Object> l1, list<Object> l2) {
	typename list<Object>::iterator itr1, itr2;
	list<Object> newlist;

	itr1 = l1.begin();
	itr2 = l2.begin();
	while (itr1 != l1.end() || itr2 != l2.end()) {
		if (*itr1 == *itr2) {
			newlist.push_back(*itr1);
			itr1++;
			itr2++;
		} else if (*itr1 < *itr2) {
			itr1++;
		} else {
			itr2++;
		}
	}
	return newlist;
}

template <typename Object>
list<Object> myunion(list<Object> l1, list<Object> l2) {
	typename list<Object>::iterator itr1, itr2;
	list<Object> newlist;

	itr1 = l1.begin();
	itr2 = l2.begin();
	while (itr1 != l1.end() || itr2 != l2.end()) {
		if (*itr1 != *itr2) {
			newlist.push_back(*itr1);
			newlist.push_back(*itr2);
		} else {
			newlist.push_back(*itr1);
		} 
		if (itr1 != l1.end()) itr1++;
		if (itr2 != l2.end()) itr2++;
	}
	return newlist;
}

int main() {
	list<int> myints;
	list<int> theyints;
	list<int> reti;
	list<int> retu;
	list<int>::iterator i;

	myints.push_back(5);
	myints.push_back(12);
	myints.push_back(11);
	myints.push_back(78);
	
	theyints.push_back(6);
	theyints.push_back(12);
	theyints.push_back(11);
	theyints.push_back(66);
	
	reti = myintersect(myints, theyints);	
	retu = myunion(myints, theyints);	
	
	cout << "Set 1: ";
	for (i = myints.begin(); i != myints.end(); i++) {
		cout << *i << ',';
	}
	cout << endl;
	
	cout << "Set 2: ";
	for (i = theyints.begin(); i != theyints.end(); i++) {
		cout << *i << ',';
	}
	cout << endl;
	
	cout << "Intersect: ";
	for (i = reti.begin(); i != reti.end(); i++) {
		cout << *i << ',';
	}
	cout << endl;
	
	std::cout << "Union: ";
	for (i = retu.begin(); i != retu.end(); i++) {
		cout << *i << ',';
	}
	cout << endl;
	return 0;
}
