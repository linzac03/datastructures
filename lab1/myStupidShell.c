#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int makeargv(const char *s, const char *delimiters, char ***argvp);

int myStupidShell (int numtok, char **argv, int stupid, char *com) {	
	char delim[] = " \t";
	int i;
	char **myargv;		
	pid_t pid;
	char *newenviron[] = {NULL};
	int numtokens;
	
	if (stupid) {
		if ((numtokens = makeargv(com, delim, &myargv)) == -1) {
			fprintf(stderr, "Failed to construct an argument array for %s\n", argv[1]);
			return 1;
		}
		printf("The argument array contains %d: \n", numtokens);
		for(i=0; i<numtokens; i++) printf("%d: %s\n", i, myargv[i]);

		if ((pid = fork()) == 0) {
			printf("I am the child: %u\n", getpid());
			printf("Execing command...\n");
			execve(myargv[0], myargv, newenviron);
			perror("execve");	/* no return on error */
			printf("> ");
			//exit(EXIT_FAILURE);
		} else {
			printf("I am the parent: %u and my child is: %u\n", getpid(), pid);
			printf("> ");
			//exit(EXIT_SUCCESS);
		}
		return 0;	
	}
	
	if ((numtokens = makeargv(argv[1], delim, &myargv)) == -1) {
		fprintf(stderr, "Failed to construct an argument array for %s\n", argv[1]);
		return 1;
	}

	printf("The argument array contains %d: \n", numtokens);
	for(i=0; i<numtokens; i++) printf("%d: %s\n", i, myargv[i]);
	return 0;
}

int main (int argc, char **argv) {
	char com[255];
	int i;
	int numtokens = argc;
	int stup = 0;
	while(1) {
		if (!argv[1] && !stup) { 
			fprintf(stderr, "Usage: %s string\n", argv[0]);
			return 1;
		}
		myStupidShell(numtokens, argv, stup, com);
		printf("> ");
		fgets(com, sizeof(com), stdin);
		if (stup == 0) stup = 1;
	}
	return 0;
}
