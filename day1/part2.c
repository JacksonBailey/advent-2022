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

--- Part Two ---

By the time you calculate the answer to the Elves' question, they've already
realized that the Elf carrying the most Calories of food might eventually run
out of snacks.

To avoid this unacceptable situation, the Elves would instead like to know the
total Calories carried by the top three Elves carrying the most Calories. That
way, even if one of those Elves runs out of snacks, they still have two backups.

In the example above, the top three Elves are the fourth Elf (with 24000
Calories), then the third Elf (with 11000 Calories), then the fifth Elf (with
10000 Calories). The sum of the Calories carried by these three elves is 45000.

Find the top three Elves carrying the most Calories. How many Calories are those
Elves carrying in total?

*/

int main()
{
	FILE* fp = fopen("1/input.txt", "r");
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	if (NULL == fp) {
		exit(EXIT_FAILURE);
	}

	int elfTotalCalories = 0;
	int elves[1];
	int currentElf = 0;
	while ((read = getline(&line, &len, fp)) != -1) {
		if (read == 1) {
			// End of current eld's snacks
			elves[currentElf] = elfTotalCalories;
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
	for (int i = 0; i < currentElf; i++) {
		if (elves[i] > maxCalories) {
			maxCalories = elves[i];
		}
	}
	printf("%d\n", maxCalories);
	exit(EXIT_SUCCESS);
}
