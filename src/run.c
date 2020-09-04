#include "run.h"

#define MAX_STACK_SIZE    1000

/*
 * Instructions:
 * 00000000 x:   lambda x
 * 01000000 x y: (x y)
 * 1n x:         De Bruijn index x on n bytes.
 */

Environment *stack;

static void
push(Closure c, Environment *stack)
{
	stack->c[stack->top++] = c;
}

static void
pop(Environment *e)
{
	
}

static void
app(Term l, Term r, Environment e)
{
	push(mkclosure(r, e), stack);
	eval(l, e);
}
