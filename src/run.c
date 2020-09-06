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

static Closure
mkclosure(Term t, Environment *e)
{
	return (Closure){
		.t = t,
		.e = e
	};
}

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
lam(Term t, Environment *e)
{
	push(pop(stack), e);
	eval(t, e);
}

static void
zero(Environment *e)
{
	Closure c;

	c = pop(e);
	eval(c.t, c.e);
}

static void
succ(int n, Environment *e)
{
	for (; n > 0; --n) (void)pop(e);
	zero(e);
}

static void
eval(Term t, Environment *e)
{
	
}
