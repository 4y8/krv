#include "src/common.h"

static struct command {
	char *name;
	void (*fun)(char *);
} commands[] = {
	{"dis", dis_main},
	{"run", run_main}
};

int
main(int argc, char **argv)
{
	int i;
	
	for (i = 0; i < (sizeof(commands) / sizeof(struct command)); ++i)
		if (!strcmp(commands[i].name, argv[1])) break; 
	commands[i].fun(argv[2]);
}
