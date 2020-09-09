#include "dis.h"
#include "common.h"

static int
print_expr(FILE *in)
{
	int c;

	c = read_bit(in);
	if (c == 0) {
		c = read_bit(in);

		if (c == 0) {
			printf("λ ");
			return print_expr(in);
		} else if (c == 1) {
			printf("(");
			if (!print_expr(in)) {
				fprintf(stderr,
				        "error: application with only 1 operand\n");
				exit(1);
			}
			printf(" ");
			int r =	print_expr(in);
			printf(")");
			return r;
		} else {
			/* Otherwise it's an EOF. */
			fprintf(stderr, "error: unknown instruction");
			exit(1);
		}
	} else if (c == 1) {
		int i = 0;
		while ((c = read_bit(in)) == 1)
			++i;
		if (c != 0) {
			fprintf(stderr, "error: unknown instruction");
			exit(1);
		}
		printf("%d", i);
		return 1;
	} else {
		return 0;
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
