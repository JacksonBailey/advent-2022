#include <stdio.h>
#include <stdlib.h>

// https://adventofcode.com/2022/day/2

FILE *open(int argc, char *argv[])
{
	if (argc < 2) {
		printf("No file specified!\n");
		exit(EXIT_FAILURE);
	}

	FILE *fp = fopen(argv[1], "r");

	if (NULL == fp) {
		printf("Oops, cannot read file\n");
		exit(EXIT_FAILURE);
	}

	return fp;
}

// core for the shape you selected (1 for Rock, 2 for Paper, and 3 for Scissors)
// plus the score for the outcome of the round (0 if you lost, 3 if the round
// was a draw, and 6 if you won).

int main(int argc, char *argv[])
{
	FILE *fp = open(argc, argv);

	char *line = NULL;
	size_t linecap = 0;
	ssize_t linelen;

	while ((linelen = getline(&line, &linecap, fp)) > 0) {
		printf("%s", line);
	}
	free(line);
	fclose(fp);

	exit(EXIT_SUCCESS);
}
