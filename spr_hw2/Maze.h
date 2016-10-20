#include <vector>
#include "DisjSets.h"

class Maze {
	public:
		Maze(int width, int height);
		void print(int mod);
	private:	
		void buildPath(char dir, int xi, int yi);
		void emptyPath(); 
		void delWall();
		int selectWall(int root, int width);
		void generate(int width);
		DisjSets dsjs;
		vector<char> path; 
};
