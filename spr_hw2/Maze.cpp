#include "Maze.h"
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
//DisjSets dsjs;
//vector<vector<char>> path; 

Maze::Maze(int width, int height) 
	: path(height*width, '.'), dsjs(width*height) {
	generate(width);	
}

void Maze::buildPath(char dir, int xi, int yi) {
	
}

void Maze::emptyPath() {

}
 
void Maze::delWall() {

}

void Maze::print(int mod) {	
	int i = 0;
	for(char c : path) {		
		i++;
		std::cout << c << " ";
		if ((i % mod) == 0) std::cout << std::endl;
	}
	std::cout << std::endl;
}

int Maze::selectWall(int root, int width) {
	int rando;
	bool right = root%width == width-1; 
	bool left = root%width == 0; 
	bool up = root < width; 
	bool down = root > dsjs.size()-width;
	bool toprc = up && right;
	bool toplc = up && left;
	bool botrc = down && right;
	bool botlc = down && left;

	while (dsjs.isDisjoint()) {	
		rando = rand()%4; //for the wall
		if (dsjs.find(root) != root) return -1;
		switch (rando) {
			case 0: //right
				if (right || toprc || botrc) continue;
				path[root] = '_';
				return root+1; 
			case 1: //left
				if (left || toplc || botlc) continue;
				path[root] = '_';
				return root-1;
			case 2: //up
				if (up || toplc || toprc) continue;
				path[root] = '|';
				return root-width;
			case 3: //down
				if (down || botlc || botrc) continue;
				path[root] = '|';
				return root+width;
		}
	}
}

void Maze::generate(int width) {
	int rd;
	srand(time(NULL));
	int size = dsjs.size();
	int raroot = rand() % size;
	int curoot = 0;

		
	print(width);	
	while(dsjs.isDisjoint()) {
		rd = selectWall(curoot, width);
		if (rd >= 0) {
			dsjs.unionSets(curoot,rd);
		}
		
		//std::cout << curoot << "; ";
		srand(time(NULL));
		curoot++;
		//curoot = rand() % size;
	}	
	std::cout << endl;
	print(width);	
}


