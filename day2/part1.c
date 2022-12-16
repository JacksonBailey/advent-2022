#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

// a = rock, b = paper, c = scissors
// x = rock, y = paper, z = scissors

// core for the shape you selected (1 for Rock, 2 for Paper, and 3 for Scissors)
// plus the score for the outcome of the round (0 if you lost, 3 if the round
// was a draw, and 6 if you won).

bool compare(const char *s1, const char *s2)
{
	return strcmp(s1, s2) == 0;
}

int main(int argc, char *argv[])
{
	FILE *fp = open(argc, argv);

	char *line = NULL;
	size_t linecap = 0;
	ssize_t linelen;

	int score = 0;
	int index = 1;
	while ((linelen = getline(&line, &linecap, fp)) > 0) {
		int roundScore;
		for (int i = 0; i < linelen; i++) {
			if (line[i] == 'A' || line[i] == 'X') {
				line[i] = 'R';
			} else if (line[i] == 'B' || line[i] == 'Y') {
				line[i] = 'P';
			} else if (line[i] == 'C' || line[i] == 'Z') {
				line[i] = 'S';
			}
		}
		if (compare(line, "R R\n")) {
			roundScore = 1 + 3;
		} else if (compare(line, "R P\n")) {
			roundScore = 1 + 0;
		} else if (compare(line, "R S\n")) {
			roundScore = 1 + 6;
		} else if (compare(line, "P R\n")) {
			roundScore = 2 + 6;
		} else if (compare(line, "P P\n")) {
			roundScore = 2 + 3;
		} else if (compare(line, "P S\n")) {
			roundScore = 2 + 0;
		} else if (compare(line, "S R\n")) {
			roundScore = 3 + 0;
		} else if (compare(line, "S P\n")) {
			roundScore = 3 + 6;
		} else if (compare(line, "S S\n")) {
			roundScore = 3 + 3;
		} else {
			printf("None match, '%s'", line);
			exit(EXIT_FAILURE);
		}
		score += roundScore;
		printf("index: %d\troundScore: %d\tscore: %d\tline: %s", index, roundScore, score, line);
		index += 1;
	}
	free(line);
	fclose(fp);

	printf("%d\n", score);

	exit(EXIT_SUCCESS);
}
