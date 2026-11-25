#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

// fixed size buffer based on assumptions about the maximum size that is likely necessary to exercise all aspects of the target function
#define SIZE 100
#define MAX 10

int main(int argc, char* argv[]) {
	if((argc == 2) && strcmp(argv[1], "echo") == 0) {
		// make sure buffer is initialized to eliminate variable behaviour that isn't dependent on the input.
		char input[SIZE] = {0};

		ssize_t length;
		length = read(STDIN_FILENO, input, SIZE);

		lib_echo(input, length);
	} else if ((argc == 2) && strcmp(argv[1], "mul") == 0) {
		int a,b = 0;
		char input[MAX] = {0};
		read(STDIN_FILENO, input, MAX);
		a = atoi(input);
		read(STDIN_FILENO, input, MAX);
		b = atoi(input);
		int res = lib_mul(a,b);
		printf("%d\n", res);
	} else {
		printf("Usage: %s mul|echo\n", argv[0]);
	}
}
