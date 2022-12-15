#include <stdio.h>
#include <stdlib.h>

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
