#include "employee.cpp"
#include "chainedhash.cpp"
#include <iostream>

using namespace std;

int main() {
	HashTable<Employee> h1;
	Employee e1("abc", 10, 1);
	Employee e2("def", 11, 2);
	Employee e3("ghi", 12, 3);
	Employee e4("jkl", 13, 4);

	h1.insert(e1);
	h1.insert(e2);
	h1.insert(e3);

	if (h1.contains(e1))
		cout << "E1 is in table" << endl;
	else
		cout << "E1 is not in table" << endl;
	if (h1.contains(e4))
		cout << "E4 is in table" << endl;
	else
		cout << "E4 is not in table" << endl;

	cout << "removing E1..." << endl;
	h1.remove(e1);
	if (h1.contains(e1))
		cout << "E1 is in table" << endl;
	else
		cout << "E1 is not in table" << endl;

}
