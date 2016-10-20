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

    void insert( const Comparable & x );
    void deleteMin( );
    void deleteMin( Comparable & minItem );
    void makeEmpty( );

  private:
    int               currentSize;  // Number of elements in heap
    std::vector<Comparable> array;        // The heap array

    void buildHeap( );
    void percolateDown( int hole );
};

#endif
