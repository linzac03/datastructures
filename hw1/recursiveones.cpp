#include <iostream>
using namespace std;
int routine(int x, int acc) {
	if (x % 2) acc += 1;	
	x >>= 1;
	if (x == 0) {
		cout << acc << " ones" << endl;
		return 0; 
	}
	routine(x, acc);
}

int main() {
	int i;
	cout << "Number: ";
	cin >> i;
	routine(i, 0);
	return 0;	
}
