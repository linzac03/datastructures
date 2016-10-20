#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	pid_t pid;

	if ((pid = fork()) == 0) {
		printf("I am the child: %u\n", getpid());
		exit(1);
	} else {
		printf("I am the parent: %u and my child is: %u\n", getpid(), pid);
		exit(1);
	}
}
