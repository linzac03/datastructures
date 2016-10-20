
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	pid_t pid;
	char *newargv[] = {"./myecho", "hello", "world", NULL };
	char *newenviron[] = {NULL};

	if ((pid = fork()) == 0) {
		printf("I am the child: %u\n", getpid());
		printf("Execing the myecho image\n");
		execve(newargv[0], newargv, newenviron);
		perror("execve");	/* no return on error */
		exit(EXIT_FAILURE);
	} else {
		printf("I am the parent: %u and my child is: %u\n", getpid(), pid);
		exit(EXIT_SUCCESS);
	}
}










