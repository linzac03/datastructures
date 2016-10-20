#include "BST_soln_b.h"
#include <iostream>

template <typename Object>
class Set {
	private:
		BST<Object> * set;
		int s;
	public:
		Set() : set(new BST<Object>()) {}

		~Set() {
			delete set;
		}

		bool empty() {
			return set->empty();
		}
	
		void insert(const Object & val) {
			set->insert(val);
			++s;
		}
	
		bool contains(const Object & val) {
			return set->find(val);
		}

		typename List<Object>::const_iterator begin() {
			return set->begin();
		}

		typename List<Object>::const_iterator end() {
			return set->end();
		}

		void remove(const Object & val) {
			set->deleteNode(val);
			--s;
		} 

		Set<Object> set_union(Set<Object> * vals) {
			Set<Object> * s = new Set<Object>();
			typename List<Object>::const_iterator mitr = set->begin();
			typename List<Object>::const_iterator vitr = vals->begin();

			while(mitr != set->end() || vitr != vals->end()) {
				if (mitr != set->end() && !s->contains(*mitr)){
					s->insert(*mitr);
				}
				if (vitr != vals->end() && !s->contains(*vitr)){
					s->insert(*vitr);
				}
				mitr++;
				vitr++;
			}
			
			return *s;	
		}
		
		Set<Object> set_intersect(Set<Object> * vals) {
			Set<Object> * s = new Set<Object>();
			typename List<Object>::const_iterator mitr = set->begin();
			typename List<Object>::const_iterator vitr = vals->begin();

			while(mitr != set->end() || vitr != vals->end()) {
				if (mitr != set->end() && !s->contains(*mitr) && vals->contains(*mitr)){
					s->insert(*mitr);
				}
				if (vitr != vals->end() && !s->contains(*vitr) && set->find(*vitr)){
					s->insert(*vitr);
				}
				mitr++;
				vitr++;
			}
			
			return *s;	
		}

	  bool subset(Set & vals) const { 
			typename List<Object>::const_iterator itr = vals->begin();
			while(itr != vals->end()) {
				if(!set.contains(*itr)) {
					return 0;
				}
				itr++;
			}
			return 1;
		}
		
		bool operator==(Set & vals) {
		if (size() == vals->size()) {	
			typename List<Object>::const_iterator itr = vals->begin();
			typename List<Object>::const_iterator itr2 = set->begin();
			while (itr != vals->end()) {
				if (!set.contains(*itr)) {
					return 0;
				}
			}
		}
			return 1;
		}
		
		int size() const{
			return s;
		}
};

