// while loop
#include <iostream>
#include <vector>

/**
 * Return median of left, center, and right.
 * Order these and hide the pivot.
 */
template <typename Comparable>
const Comparable & median3( std::vector<Comparable> & a, int left, int right )
{
    int center = ( left + right ) / 2;
    if( a[ center ] < a[ left ] )
        std::swap( a[ left ], a[ center ] );
    if( a[ right ] < a[ left ] )
        std::swap( a[ left ], a[ right ] );
    if( a[ right ] < a[ center ] )
        std::swap( a[ center ], a[ right ] );

        // Place pivot at position right - 1
    std::swap( a[ center ], a[ right - 1 ] );
    return a[ right - 1 ];
}

/**
 * Simple insertion sort.
 */
template <typename Comparable>
void insertionSort( std::vector<Comparable> & a, int left, int right )
{
		int j;
    for( int p = left; p <= right; p++ )
    {
        Comparable tmp = a[ p ];
        for( j = p; j > 0 && tmp < a[ j - 1 ]; j-- )
            a[ j ] = a[ j - 1 ];
        a[ j ] = tmp;
    }
}

/**
 * Internal quicksort method that makes recursive calls.
 * Uses median-of-three partitioning and a cutoff of 10.
 * a is an array of Comparable items.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <typename Comparable>
void quicksort( std::vector<Comparable> & a, int left, int right ) {
	while (left + 10 <= right) {
		Comparable pivot = median3( a, left, right );

				// Begin partitioning
		int i = left, j = right - 1;
		for( ; ; )
		{
				while( a[ ++i ] < pivot ) { }
				while( pivot < a[ --j ] ) { }
				if( i < j )
						std::swap( a[ i ], a[ j ] );
				else
						break;
		}

		std::swap( a[ i ], a[ right - 1 ] );  // Restore pivot

		quicksort( a, left, i - 1 );     // Sort small elements
		quicksort( a, i + 1, right );    // Sort large elements
	} 
	insertionSort( a, left, right );
}

void quicksort(std::vector<int> & arr) {
	quicksort(arr, 0, arr.size() - 1);
}

int main() {
	std::vector<int> arr{4,2,7,3,62,7,9,443,2};
	for(std::vector<int>::const_iterator i = arr.begin(); 
			i != arr.end(); i++) {
		std::cout << *i << ' ';
	}
	std::cout << std::endl;
	quicksort(arr);
	for(std::vector<int>::const_iterator i = arr.begin(); 
			i != arr.end(); i++) {
		std::cout << *i << ' ';
	}
	std::cout << std::endl;
}
