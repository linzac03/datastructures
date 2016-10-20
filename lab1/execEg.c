#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	char *newargv[] = {"./myecho", "hello", "world", NULL };
	char *newenviron[] = {NULL};

	execve(newargv[0], newargv, newenviron);
	perror("execve");	/* no return on error */
	exit(EXIT_FAILURE);
}









