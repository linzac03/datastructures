#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;


int routine(int argc, char** argv) {
	string s;
	ssize_t ssz;
	size_t sz;
	char *buff = NULL;
	char *newfile = NULL;
	int i = 0;
	FILE *r_fd = NULL;
	FILE *w_fd = NULL;	
	
	if (argc != 3) {
		printf("Usage: openRW infile outfile\n");
		exit(1);
	}
	cout << "Opening file: " << argv[1] << endl;
	r_fd = fopen(argv[1], "r");
	if (r_fd == NULL) {
		printf("Error on open r file(s)\n");
		exit(1);
	}
	while ((ssz = getline(&buff, &sz, r_fd)) > 0) {		
		if (buff[0] == '#' && buff[1] == 'i') {
	
			newfile = &buff[10];
			while (true) {
				if (newfile[i] == '>' || newfile[i] == '"') {
					newfile[i] = '\0';
					break;
				}		
				i += 1;
			}
			argv[1] = newfile;
			routine(argc, argv);		

		} else {	
			cout << buff << endl;		
			w_fd = fopen(argv[2], "w");
			if (w_fd == NULL) {
				printf("Error on open w file(s)\n");
				exit(1);
			}
			
			fwrite(buff, ssz, sizeof(char), w_fd);
		
		}
	}
}
	


int main(int argc, char** argv) {
	routine(argc, argv);
	return 0;
}
