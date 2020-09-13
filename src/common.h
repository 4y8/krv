#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <string.h>
#include "run.h"
#include "dis.h"

char read_bit(FILE *);
void write_bit(char, FILE *);
void fclose_bit(FILE *);

#endif /* common.h */
