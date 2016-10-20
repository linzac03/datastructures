#include <vector>
#include <queue>
#include <iostream>

class Graph {
	public:
		struct Node {
			char *name;
			int indegree;
			int topNum;
			std::vector<Node> adjList;
			Node(char *id, std::vector<Node> edges) 
				: name(id), indegree(0), adjList(edges) {}
		};

		Graph() {}
		~Graph() {}

		void insert(Node & newNode) {
			grph.push_back(newNode);		
			update();	
		}

		std::queue<Node> topsort() {
			std::queue<Node> q;
			int counter = 0;

			for (Node n : grph) {
				if( n.indegree == 0 )
					q.push( n );
			}
			while( !q.empty( ) ) {
				Node n = q.front( );
				q.pop( );
				n.topNum = ++counter; // Assign next number
				for (Node m : n.adjList) {
					if( --m.indegree == 0 ) {
						q.push( m );
					}
				}
			}
			
			if( counter != grph.size() ) {
				std::cout << "Cycle detected" << std::endl;
				return q;
			}
			grph.clear();
			return q;
		}		

	private:
		std::vector<Node> grph;
	
		void update() {
			std::vector<Node> tmp = grph;

			for (Node n : grph) {
				n.indegree = 0;
				for (Node m : tmp) {
					for (Node a : m.adjList) {
						if (n.id == a.id) n.indegree++;
					}
				}
			}
		}
};
