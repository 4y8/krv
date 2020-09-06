#include "dis.h"

static int 
print_expr(FILE *in)
{
	int c;

	c = fgetc(in);
	switch (c) {
	case 0:
		printf("λ ");
		return print_expr(in);
	case 0b01000000:
		printf("(");
		if (!print_expr(in)) {
			fprintf(stderr,
			        "error: application with only 1 operand\n");
			exit(1);
		}
		int r =	print_expr(in);
		printf(")");
		return r;
	case 0b10000000: {
		short i;
		fread(&i, sizeof(short), 1, in);
		printf("%hd", i);
		return 1;
	}
	case EOF:
		return 0;
	default:
		fprintf(stderr, "error: unknown instruction\n");
		exit(1);
	}
}

void
dis_main(char *file)
{
	FILE *in;

	in = fopen(file, "r");
	if (!in) {
		fprintf(stderr, "error: couldn't open %s\n", file);
		exit(1);
	}
	for ( ; print_expr(in); );
	(void)fclose(in);
}
