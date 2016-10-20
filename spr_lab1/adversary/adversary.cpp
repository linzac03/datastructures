#include <iostream>

int u, v, a, b, t;
int arr[] = {1,7,3,6,4};

void process() {
	int size = sizeof(arr)/sizeof(arr[0]);
	//initially set a and b
	if (arr[size-1] < arr[size]) {
		a = arr[size];
		b = arr[size-1];
	}
	//reduce relevant size
	size -= 2;
	//step through rest of array
	t = (sizeof(arr)/sizeof(arr[0])) % 2;
	while (size > t) {
		if (arr[size-1] < arr[size]) {	
			u = arr[size];
			v = arr[size-1];
		} else {
			u = arr[size-1];
			v = arr[size];
		}
		a = u > a ? u : a;
		b = v < b ? v	: b;
		size -= 2;
	}
	//check for leftover in an odd length array
	if (t > 0) {
		a = arr[0] > a ? arr[0] : a;
		b = arr[0] < b ? arr[0] : b;
	}
}

int main () {
	process();
	std::cout << "Max: " << a << std::endl;
	std::cout << "Min: " << b << std::endl;
}
