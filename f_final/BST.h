

/*
 * This version does a const_iterator from an inorder traversal
 * It is not as general as some iterators because trees have invariants that
 * can't be altered using an iterator.  The alternative  to using the inorder
 * traversal is to traverse the tree for each access OR to keep a list of tree
 * nodes.
 */

#include "list.h"
#include <iostream>
#include <cstdlib>
using namespace std;

template <typename Object>
class BST {
   private:
	struct BSTNode {
        Object  data;
        BSTNode   *left;
        BSTNode   *right;

        BSTNode( const Object & d = Object( ), BSTNode *l = NULL, BSTNode *r = NULL )
          : data( d ), left( l ), right( r ) { }
	};

	public:

	class const_iterator {
	public:
	/*
	 * Warning no release of dynamically allocated list
	 */
			const_iterator() : elements(NULL), it_cur(NULL), it_end(NULL) 
				{}

			bool hasMore() const {
				return it_cur != it_end;
			}

			const Object & operator* () const {
				return *it_cur;
			}

			const_iterator & operator++ () {
				++it_cur;
				return *this;
			}

			const_iterator & operator++(int) {
				it_cur++;
				return *this;
			}

			bool operator== (const const_iterator & rhs ) const {
				return it_cur == rhs.it_cur;
			}

			bool operator != (const const_iterator & rhs) const {
				return !(*this == rhs);
			}

	private:
		List<Object> *elements;
		typename List<Object>::const_iterator it_cur;
		typename List<Object>::const_iterator it_end;

		const_iterator(BST & t) {
	 		elements = t.inorder();
			it_cur = elements->begin();
			it_end = elements->end();
		}

		friend class BST<Object>;



	
	};



   public:

	BST(): root(NULL) {}
    
	~BST( )
	{
		clear( );
		delete root;
	}


	bool empty() {
		return root == NULL;
	}

	void insert(const Object & o) {
		insert(o, root);
	}	
	bool find(const Object &o) {
		return find(o, root);
	}
/*
 * This is a partial function since findMin or findMax are undefined
 * in an empty tree.
 */

	Object findMin() {
		if (!root)
			return Object{};
		return findMin(root);
	}

	Object findMax() {
		if (!root)
			return Object{};
		return findMax(root);
	}

    List<Object> * inorder() {
        List<Object> * l = new List<Object>();
        if (root)
            doInOrder(root, l);

        return l;
    }


	int height() {
		if (!root)
			return 0;
		else
			return recHt(root);
	}
	
	int heightDiff () {
 		return heightDiff(root); 
	}	
	
	bool operator== (const BST<Object> & t) {
		List<Object> l1 = inorder();
		List<Object> l2 = t.inorder();
		List<Object>::iterator itr1 = l1.begin();
		List<Object>::iterator itr2 = l2.begin();
		// do these lists have ==?? return l1 == l2?
		if (l1.size() != l2.size()) {
			return false;
		}	
		while (itr1 != l1.end() && itr2 != l2.end()) {
			if (*itr1 != *itr2) return false;
			itr1++;
			itr2++;
		}
		return true;				
	}

	void deleteNode(const Object & o) {
		if (!root)
			return;
		deleteRec(o, root);
	}

	const_iterator begin() {
		return const_iterator(*this);
	}



private:

/*
 * This section includes the utilities that work directly on the BSTNode
 * representation
 */


/*
 * This is an explicit pointer version. You could use
 * a reference to the pointer which would require less
 * syntax, but this version makes the addresses explicit.
 * See BST5c
 */

	void insert(const Object & o, BSTNode *& cur) {

			if (cur == NULL) 
				cur = new BSTNode(o);
			else if (cur->data == o)
				return;
			else if (o < cur->data) 
				insert(o, cur->left);
			else 
				insert(o, cur->right);
	}
		

	bool find(const Object &o, BSTNode *cur) {
		if (!cur)
			return 0;
		if (cur->data == o)
			return 1;
		else if (cur->data > o)
			return find(o, cur->left);
		else
			return find(o, cur->right);
	}

	Object findMin(BSTNode *cur) {
		if (cur->left)
			return findMin(cur->left);
		return cur->data;
	}


	Object findMax(BSTNode *cur) {
		if (cur->right)
			return findMax(cur->right);
		return cur->data;
	}

    void doInOrder(BSTNode * c, List<Object> * l) {
        if (!c)
            return;
        else {
            doInOrder(c->left, l);
            l->push_back(c->data);
            doInOrder(c->right, l);
        }
    }

	int recHt(BSTNode *cur) {
		if (cur == NULL)
			return 0;
		else {
			int LeftHt = recHt(cur->left);
			int RightHt = recHt(cur->right);
			return (LeftHt > RightHt ? LeftHt  : RightHt) + 1;
		}
	}
	
	int heightDiff(BSTNode *cur) {
		if (cur == NULL) return 0;
		int LeftHt = recHt(cur->left);
		int RightHt = rechHt(cur->right);
		return abs(LeftHt - RightHt);
	}

	void deleteRec(const Object & o, BSTNode *& cur) {
			if (cur == NULL)
				return;			// not in tree
			if (o<cur->data)
				deleteRec(o, cur->left);
			else if (o>cur->data)
				deleteRec(o, cur->right);
			else if (cur->left && cur->right) {
				// two kids
				cur->data = findMaxAndDel(cur->left);
			} else if (cur->left || cur->right) {
				// only one kid
				BSTNode *save = cur;
				cur = cur->left ? cur->left : cur->right;
				delete save;
			} else {
				// leaf
				BSTNode *save = cur;
				cur = NULL;
				delete save;
			}
	}

	Object findMaxAndDel(BSTNode *&cur) {
		if (cur->right)
			return findMaxAndDel(cur->right);
		BSTNode * save = cur;
		Object data = cur->data;
		cur = cur->left;
		delete save;
		return data;
	}


	void clear() {
		// Not implemented yet
	}

		
  private:
    BSTNode *root;

};
