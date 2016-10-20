#include "BHeap.h"
#include <iostream>
#include <exception>

struct HeapException : public std::exception {
        const char *what() const throw () {
                return "Empty Heap";
        }
};

template <typename Comparable>
void BinaryHeap<Comparable>::print( ){
	typename std::vector<Comparable>::iterator st = this->array.begin();
	while (st != this->array.end()) {
		std::cout << *st << " ";
		st++;
	}
	std::cout << std::endl;
}

template <typename Comparable>
void BinaryHeap<Comparable>::insert( Comparable & x ){
	if( this->currentSize == this->array.size( ) - 1 )
			this->array.resize( this->array.size( ) * 2 );

			// Percolate up
	int hole = ++this->currentSize;
	for( ; hole > 1 && x < this->array[ hole / 2 ]; hole /= 2 )
			this->array[ hole ] = this->array[ hole / 2 ];
	this->array[ hole ] = x;
}

template <typename Comparable>
void BinaryHeap<Comparable>::deleteMin( ){
	if( this->isEmpty( ) )
		throw HeapException( );
	this->array[ 1 ] = this->array[ this->currentSize-- ];
	this->array[ this->currentSize + 1 ] = *emptyJob;
  BinaryHeap<Comparable>::percolateDown( 1 );
}

template <typename Comparable>
Comparable & BinaryHeap<Comparable>::getMin( ){
	if( this->isEmpty( ) )
		throw HeapException( );

	return this->array[ 1 ];
}

template <typename Comparable>
void BinaryHeap<Comparable>::dectimer( ){
	typename std::vector<Comparable>::iterator beg = this->array.begin();
	typename std::vector<Comparable>::iterator en = this->array.end();
	for(beg; beg!=en; beg++) {
		(*beg)--; //decrease timers by one
	}
}

template <typename Comparable>
void BinaryHeap<Comparable>::deleteMin( Comparable & minItem ){
	if( this->isEmpty( ) )
		throw HeapException( );

	minItem = this->array[ 1 ];
	this->array[ 1 ] = this->array[ this->currentSize-- ];
	this->array[ this->currentSize + 1 ] = *this->emptyJob;
	BinaryHeap<Comparable>::percolateDown( 1 );
}

template <typename Comparable>
void BinaryHeap<Comparable>::percolateDown( int hole ){
	int child;
	Comparable & tmp = this->array[ hole ];

	for( hole; hole * 2 <= this->currentSize; hole = child ){
		child = hole * 2;
		if( child != this->currentSize && this->array[ child + 1 ] < this->array[ child ] )
				child++;
		if( this->array[ child ] < tmp )
				this->array[ hole ] = this->array[ child ];
		else
				break;
	}
	this->array[ hole ] = tmp;
}

template <typename Comparable>
BinaryHeap<Comparable>::BinaryHeap( const std::vector<Comparable> & items )
	: array( items.size( ) + 10 ), currentSize( items.size( ) ), emptyJob( new Comparable() ){
	for( int i = 0; i < items.size( ); i++ )
		this->array[ i + 1 ] = items[ i ];
	BinaryHeap<Comparable>::buildHeap( );
}

template <typename Comparable>
BinaryHeap<Comparable>::BinaryHeap( int capacity )
	: array( capacity ), currentSize( 0 ), emptyJob( new Comparable() ) {}

template <typename Comparable>
void BinaryHeap<Comparable>::buildHeap( ) {
	for( int i = this->currentSize / 2; i > 0; i-- )
		BinaryHeap<Comparable>::percolateDown( i );
}
