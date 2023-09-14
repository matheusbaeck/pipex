#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
	if (!fork())
		exit(1);
	int status;
	int pid = waitpid(-1, &status, 0);
	printf("%d\n", WEXITSTATUS(status));
}
