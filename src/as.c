#include "common.h"

static void get_expr(FILE *, FILE *);

static void
get_expr(FILE *in, FILE *out)
{
	int c;

	/* Skip spaces. */
	while ((c = fgetc(in)) == ' ');
	if (isdigit(c)) {
		int i = c - '0';
		while (isdigit(c = fgetc(in))) {
			i *= 10;
			i += c - '0';
		}
		ungetc(c, in);
		printf("%d\n", i);
		for (; i >= 0; --i)
			write_bit(1, out);
		write_bit(0, out);
	} else if (c == 0xCE) {
		c = fgetc(in);
		if (c == 0xBB) {
			write_bit(0, out);
			write_bit(0, out);
			get_expr(in, out);
		}
	} else if (c == '\\') {
		write_bit(0, out);
		write_bit(0, out);
		get_expr(in, out);
	} else if (c == '(') {
		write_bit(0, out);
		write_bit(1, out);
		get_expr(in, out);
		get_expr(in, out);
		if (fgetc(in) == ')')
			ungetc(')', in);
		else {
			printf("unexpected character");
			exit(1);
		}
	}
}

void
as_main(char *file)
{
	int c;
	FILE *in, *out;

	in = fopen(file, "r");
	if (!in) {
		printf("couldn't open file %s\n", file);
		exit(1);
	}
	out = fopen("a.out", "w");
	if (!out) {
		printf("couldn't open file a.out\n");
		exit(1);
	}
	get_expr(in, out);
	fclose_bit(out);
	(void)fclose(in);
}
