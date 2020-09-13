#include "src/common.h"

static struct command {
	char *name;
	void (*fun)(char *);
} commands[] = {
	{"dis", dis_main},
	{"run", run_main},
	{"as", as_main},
};

int
main(int argc, char **argv)
{
	int i;

	for (i = 0; i < (sizeof(commands) / sizeof(struct command)); ++i)
		if (!strcmp(commands[i].name, argv[1]))
			break;
	if (i == (sizeof(commands) / sizeof(struct command))) {
		printf("usage: krv [dis|run|as] FILE\n");
		exit(1);
	}
	commands[i].fun(argv[2]);
}
