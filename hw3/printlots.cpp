#include <iostream>
#include <list>

using namespace std;

template <typename Object>
void printLots(list<Object> L, list<int> P) {
	typename list<int>::iterator pi;
	typename list<Object>::iterator li;
	int i = 0;
	
	li = L.begin();
	pi = P.begin();
	for (pi; pi != P.end() && li != L.end(); pi++) {
			while (i < *pi-1 && li != L.end()) {
				i++;
				li++;
				cout << *li;
			}
	}	
	cout << endl;
}

int main() {
	list<int> myintlist;
	myintlist.push_back(2);
	myintlist.push_back(3);
	myintlist.push_back(4);
	list<char> mycharlist;
	mycharlist.push_back('t');
	mycharlist.push_back('h');
	mycharlist.push_back('e');
	mycharlist.push_back('y');
	printLots(mycharlist, myintlist);
}
