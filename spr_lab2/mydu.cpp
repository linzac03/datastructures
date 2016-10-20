#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stack>

int depthfirstapply(char *path, int pathfun(char *path1)) {
	DIR *dir = opendir(path);
	struct dirent *ent = nullptr;
	std::stack<char *> stk;
	char tmp[MAX_CANON];
	int dblocks = 0;	
		
	if (dir == NULL) {
		std::cout << pathfun(path) << " \t " << path << std::endl;
		return 0;
	}

	dblocks += pathfun(path);
	
	while((ent = readdir(dir)) != NULL) {
		if (strcmp(&ent->d_name[0], ".") > 0 && strcmp(&ent->d_name[0], "..") > 0) {
			if (ent->d_type == DT_DIR) {
				stk.push(&ent->d_name[0]);	
			} else {
				strncpy(tmp, path, MAX_CANON);
				strcat(tmp, &ent->d_name[0]);				
				dblocks += pathfun(tmp) > 0 ? pathfun(tmp) : 0;
			}
		} 
	}

	while (!stk.empty()) {
		strncpy(tmp, path, MAX_CANON);
		strcat(tmp, stk.top());
		strcat(tmp, "/");
		stk.pop();
		dblocks += depthfirstapply(tmp, pathfun);
	}
	std::cout << dblocks << " \t" << path << std::endl;
	closedir(dir);	
	return dblocks;
}

int sizepathfun(char *path) {
	struct stat buf;

	if (stat(path, &buf) < 0) return -1;
	//std::cout << buf.st_blocks << ", " << path << std::endl;
	return buf.st_blocks/2; //be like du
}	

int main(int argc, char **argv) {
	depthfirstapply(argv[1], sizepathfun);
}	


