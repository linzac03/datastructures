#include <iostream>

using namespace std;

template <typename Object>
class BST {
	private:
		struct BSTNode {
			Object value;
			BSTNode * left;
			BSTNode * right;
		
			BSTNode( const Object & d = Object{ }, BSTNode * p = nullptr, BSTNode * n = nullptr )
          : value{ d }, left{ p }, right{ n } { }
		};
		BSTNode * root;
	
	public:
		BST() {root = nullptr;}
		
		~BST() {delete root;}

		bool empty() {
			return root == nullptr;
		}

		void insert(Object & elem) {
			BSTNode ** curr = &root;
			while (*curr != nullptr) {
				if (elem > (*curr)->value) {
					curr = &((*curr)->right);	
				}	else {
					curr = &((*curr)->left);
				}
			}
			
			*curr = new BSTNode(elem);
		}
	
		bool member(Object & elem) {
			BSTNode * curr = root;
			while(curr->value != elem) {
				curr = (elem < curr->value) ? curr->left : curr->right;
				if (curr == nullptr) return false;
			}
			return true;
		}

		Object findMin() {
			BSTNode * curr = root;

			while(curr->left != nullptr) curr = curr->left;
			return curr->value;
		}
		
		Object findMax() {
			BSTNode * curr = root;

			while(curr->right != nullptr) curr = curr->right;
			return curr->value;
		}
	
		void deleteN(Object & elem) {
			BSTNode ** curr = &root;
			if (member(elem)) {
				while (elem != (*curr)->value) {
					curr = (elem < (*curr)->value) ? &((*curr)->left) 
																					: &((*curr)->right);		
				}
				*curr = nullptr;
			}
		}

		void printTree() {
			cout << "Hello Tree: " << endl;
			if (!empty()) {
				cout << "  " << "Root: " << root->value << endl;
				cout << "  ";
				printT(root);
				cout << endl;
			} else {
				cout << "\tEmpty Tree" << endl;
			}
		}	

		friend void printT(BSTNode * curr) {
			if (curr != nullptr) {
				printT(curr->left);
				cout << curr->value << " ";
				printT(curr->right);
			}
		}
};

int main(int argc, char **argv) {
	BST<int> myints;
	int n = 2;
	int m = 5;
	int o = 1;
	int p = 7;
	int q = 8;
	myints.insert(n);
	myints.printTree();
	myints.insert(m);
	myints.printTree();
	myints.insert(o);
	myints.printTree();
	myints.insert(p);

	myints.printTree();
	cout << "member(5): " << myints.member(m) << endl;	
	cout << "member(8): " << myints.member(q) << endl;
	cout << "Min: " << myints.findMin() << endl;
	cout << "Max: " << myints.findMax() << endl;
	cout << "Delete 7: " << endl;
	myints.deleteN(p);
	myints.printTree();	
	return 0;
}
