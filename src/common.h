#ifndef __COMMON_H__
#define __COMMON_H__

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "run.h"
#include "dis.h"
#include "as.h"

char read_bit(FILE *);
void write_bit(char, FILE *);
void fclose_bit(FILE *);

#endif /* common.h */
