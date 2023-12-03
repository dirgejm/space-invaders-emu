#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {	
	printf("Here are my entered arguments:\n");
	for (int i = 0; i < argc; i++) {
		printf("Argument %d: %s\n", i, argv[i]);
	}
	printf("\n");

	return 0;
}
