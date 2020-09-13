#include "src/common.h"

static struct command {
	char *name;
	void (*fun)(char *);
} commands[] = {
	{"dis", dis_main},
	{"run", run_main},
	{"as", as_main},
};

static void
usage(void)
{
	printf("usage: krv [dis|run|as] FILE\n");
	exit(1);
}

int
main(int argc, char **argv)
{
	int i;

	if (argc != 3)
		usage();

	/* Get the function to run according to the given parameter. */
	for (i = 0; i < (sizeof(commands) / sizeof(struct command)); ++i)
		if (!strcmp(commands[i].name, argv[1]))
			break;

	if (i == (sizeof(commands) / sizeof(struct command)))
		usage();

	commands[i].fun(argv[2]);
}
