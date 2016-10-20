

/*
 * This version keeps a list as part of its state to support
 * an iterator.
 * It then just does an inorder traversal and instantiated the
 * list with the inorder traversal and returns an iterator to
 * the list. This hides the representation from the user.
 *
 * This version does not do any resource release.
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

    List<Object> * preorder() {
        List<Object> * l = new List<Object>();
        if (root)
            doPreOrder(root, l);

        return l;
    }


	int height() {
		if (!root)
			return 0;
		else
			return recHt(root);
	}

	void deleteNode(const Object & o) {
		if (!root)
			return;
		deleteRec(o, root);
	}

	typename List<Object>::const_iterator begin() {
		l = inorder();
		return l->begin();
	}

	/*
	 * only makes sense if begin() has been called first
	 */

	typename List<Object>::const_iterator end() {
		return l->end();
	}

	int computeS() {
		return computeS(root);
	}

    bool operator== ( const BST & rhs ) const
    { return isEq(root, rhs.root); }


    int htDiff() {
        if (root == NULL)
            return 0;
        int leftHt = recHt(root->left);
        int rightHt = recHt(root->right);
        return leftHt-rightHt ;
    }

	int size() {
		return size(root);
	}





private:

/*
 * This section includes the utilities that work directly on the BSTNode
 * representation
 */

	int size(BSTNode *cur) const {
		if (cur == NULL)
			return 0;
		else return size(cur->left) + size(cur->right) + 1;
	}


	bool isEq(const BSTNode * n1, const BSTNode *n2) const {
			if (n1 == NULL && n2 == NULL)
				return 1;
			else if (n1 == NULL || n2 == NULL)
				return 0;
			else if (n1->data != n2->data)
				return 0;
			else
				return isEq(n1->left, n2->left) && isEq(n1->right, n2->right);
	}

	int computeS(BSTNode * cur) {
		if (cur == NULL)
			return 0;
		else {
			int leftS = computeS(cur->left);
			int rightS = computeS(cur->right);
			return 1 + (leftS>rightS ? rightS : leftS);
		}
	}


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

    void doPreOrder(BSTNode * c, List<Object> * l) {
        if (!c)
            return;
        else {
            l->push_back(c->data);
            doPreOrder(c->left, l);
            doPreOrder(c->right, l);
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
	List<Object> *l;			// used for the iterator

};
