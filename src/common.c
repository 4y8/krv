#include "common.h"

static int bit_pos = 7;
static int current_byte;

int
read_bit(FILE *in)
{
	if (bit_pos >= 0) {
		return (current_byte >> bit_pos--) && 1;
	} else {
		bit_pos = 7;
		current_byte = getc(in);
		return read_bit(in);
	}
}
