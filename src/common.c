#include "common.h"

static int rbpos = -1;
static int current_rb;

static int current_wb = 0;
static int wbpos = 7;

char
read_bit(FILE *in)
{
	if (rbpos >= 0) {
		return (current_rb >> (rbpos--)) & 1;
	} else {
		rbpos = 7;
		current_rb = getc(in);
		if (current_rb == EOF)
			return -1;
		return read_bit(in);
	}
}

void
write_bit(char bit, FILE *out)
{
	if (wbpos >= 0)
		current_wb |= (bit & 1) << (wbpos--);
	else {
		(void)putc(current_wb, out);
		wbpos = 7;
		current_wb = 0;
		write_bit(bit, out);
	}
}

void
fclose_bit(FILE *file)
{
	if (wbpos >= 0)
		(void)putc(current_wb, file);
	(void)fclose(file);
}
