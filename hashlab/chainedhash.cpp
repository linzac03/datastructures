#include <vector>
#include <string>
#include <list>

template <typename HashedObj>
class HashTable
{
  public:
    explicit HashTable( int size = 101 ) : theLists (size), currentSize (0) {};

    bool contains( const HashedObj & x ) {
			const std::list<HashedObj> & whichList = theLists[ myhash( x ) ];
			return find( whichList, x );
		}

    void makeEmpty( ) {
			for( int i = 0; i < theLists.size( ); i++ )
				theLists[ i ].clear( );
		}
    
		bool insert( const HashedObj & x ) {
			std::list<HashedObj> & whichList = theLists[ myhash( x ) ];
			if( find( whichList, x ) ) return false;
			whichList.push_back( x );
	
					// Rehash; see Section 5.5
			if( ++currentSize > theLists.size( ) )
					rehash( );
	
			return true;
		}

    bool remove( const HashedObj & x ){
			std::list<HashedObj> & whichList = theLists[ myhash( x ) ];
			typename std::list<HashedObj>::iterator st = whichList.begin();
			typename std::list<HashedObj>::iterator en = whichList.end();
			int hv = hash(x);
			if( st == en ) return false;
			while (st != en) {
				if (hash(*st) == hv) break;
				st++;
			}
			whichList.erase( st );
			--currentSize;
			return true;
		}

  private:
    std::vector<std::list<HashedObj>> theLists;   // The array of Lists
    int  currentSize;

    void rehash( ){
			int s = theLists.size();
			std::vector<std::list<HashedObj>> tmp (s + s/2);
			
			for (typename std::vector<std::list<HashedObj>>::iterator itr = theLists.begin(); itr != theLists.end(); itr++) {
				for (typename std::list<HashedObj>::iterator litr = itr->begin(); litr != itr->end(); litr++) {
					std::list<HashedObj> & whichList = tmp[ myhash( *litr ) ];
					if(find(whichList, *litr)) continue; 
					whichList.push_back(*litr);
				}
			}
			theLists = tmp;					
t program. I'll sketch those steps next from my memo	}

    int myhash( const HashedObj & x ) const {
			int hv = hash(x);
			hv %= hv + theLists.size();
			return hv;	
		}
		
		bool find(const std::list<HashedObj> & l, const HashedObj & x) const {
			typename std::list<HashedObj>::const_iterator st = l.begin();
			typename std::list<HashedObj>::const_iterator en = l.end();

			int hv = hash(x);
			while (st != en) {
				if (hash(*st) == hv) return true; 
				st++;
			}
			return false;
		}
};

int hash( const std::string & key ){
	int hashVal = 0; 
	for (int i=0; i < key.length(); i++) {
		hashVal += key[i] % key.length();
	}
	return hashVal % key.length();				
}

int hash( int key );
