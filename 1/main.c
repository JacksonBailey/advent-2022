#include <stdio.h>
#include <stdlib.h>

// https://adventofcode.com/2022/day/1

/*
The Elves take turns writing down the number of Calories contained by the
various meals, snacks, rations, etc. that they've brought with them, one item
per line. Each Elf separates their own inventory from the previous Elf's
inventory (if any) by a blank line.

For example, suppose the Elves finish writing their items' Calories and end up
with the following list:

1000
2000
3000

4000

5000
6000

7000
8000
9000

10000

This list represents the Calories of the food carried by five Elves:

    - The first Elf is carrying food with 1000, 2000, and 3000 Calories, a total
	  of 6000 Calories.
    - The second Elf is carrying one food item with 4000 Calories.
    - The third Elf is carrying food with 5000 and 6000 Calories, a total of
	  11000 Calories.
    - The fourth Elf is carrying food with 7000, 8000, and 9000 Calories, a
	  total of 24000 Calories.
    - The fifth Elf is carrying one food item with 10000 Calories.

In case the Elves get hungry and need extra snacks, they need to know which Elf
to ask: they'd like to know how many Calories are being carried by the Elf
carrying the most Calories. In the example above, this is 24000 (carried by the
fourth Elf).

Find the Elf carrying the most Calories. How many total Calories is that Elf
carrying?

*/

FILE *open(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("No file specified!\n");
		exit(EXIT_FAILURE);
	}

	FILE *fp = fopen(argv[1], "r");

	if (NULL == fp)
	{
		printf("Oops, cannot read file\n");
		exit(EXIT_FAILURE);
	}

	return fp;
}

int main(int argc, char *argv[])
{
	FILE *fp = open(argc, argv);

	char *line = NULL;
	size_t linecap = 0;
	ssize_t linelen;

	int elfTotalCalories = 0;
	int* elves = malloc(sizeof elves);
	int currentElf = 0;
	while ((linelen = getline(&line, &linecap, fp)) > 0) {
		if (linelen == 1) {
			// End of current eld's snacks
			int *tmp = realloc(elves, (currentElf + 2) * sizeof elves);
			if (tmp) {
				elves = tmp;
			} else {
				exit(EXIT_FAILURE);
			}
			elves[currentElf] = elfTotalCalories;
			//printf("elf has %d total %d\n", elves[currentElf], elfTotalCalories);
			currentElf++;
			elfTotalCalories = 0;
		} else {
			// Elf has more snacks to document, yum!
			int snackCalories = atoi(line);
			elfTotalCalories += snackCalories;
		}
	}
	free(line);
	fclose(fp);

	int maxCalories = 0;
	//printf("%d\n", currentElf);
	for (int i = 0; i < currentElf; i++) {
		if (elves[i] > maxCalories) {
			maxCalories = elves[i];
		}
	}
	printf("%d\n", maxCalories);

	exit(EXIT_SUCCESS);
}
