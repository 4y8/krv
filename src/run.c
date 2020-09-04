#include "run.h"

#define MAX_STACK_SIZE    1000

/*
 * Instructions:
 * 00000000 x:   lambda x
 * 01000000 x y: (x y)
 * 10000000 x:   De Bruijn index x (on 2 bytes).
 */

Environment *stack;
Environment *env;

static void
push(Closure c, Environment *stack)
{
	stack->c[stack->top++] = c;
}

static Closure
pop(Environment *stack)
{
	
	return stack->c[--stack->top];
}

static void
app(Term l, Term r, Environment *e)
{
	push(mkclosure(r, e), stack);
	eval(l, e);
}

static void
zero(Environment *e)
{
	Closure c;

	c = pop(env);
	eval(c.t, c.e);
}

static void
abs(Term t, Environment *e)
{
	push(pop(stack), e);
	eval(t, e);
}
