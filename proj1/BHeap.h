#ifndef BHEAP_H
#define BHEAP_H

#include <vector>

template <typename Comparable>
class BinaryHeap
{
  public:
    explicit BinaryHeap( int capacity = 100 );
    explicit BinaryHeap( const std::vector<Comparable> & items );
		~BinaryHeap();
    bool isEmpty( ) const { return currentSize == 0; }
    const Comparable & findMin( ) const;

    void insert( Comparable & x );
    void deleteMin( );
    Comparable & getMin( );
    void deleteMin( Comparable & minItem );
    void makeEmpty( );
    void dectimer( );
    void print( );

  private:
    int               currentSize;  // Number of elements in heap
    std::vector<Comparable> array;        // The heap array
    Comparable * emptyJob;
		void buildHeap( );
    void percolateDown( int hole );
};

#endif
