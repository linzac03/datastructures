    explicit BinaryHeap( const vector<Comparable> & items )
      : array( items.size( ) + 10 ), currentSize( items.size( ) )
    {
        for( int i = 0; i < items.size( ); i++ )
            array[ i + 1 ] = items[ i ];
        buildHeap( );
    }
    
    /**
     * Establish heap order property from an arbitrary
     * arrangement of items. Runs in linear time.
     */
    void buildHeap( )
    {
        for( int i = currentSize / 2; i > 0; i-- )
            percolateDown( i );
    }
