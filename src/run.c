#include <stdio.h>
#include <stdlib.h>

#include "run.h"
#include "common.h"

#define MAX_STACK_SIZE    1000

/*
 * Instructions (by John Tromp):
 * 00 x:   lambda x
 * 01 x y: (x y)
 * 1^(n + 1) 0 : De Bruijn index n
 */

Environment *stack;
Environment *env;

static Term 
get_termf(FILE *f, char *buf)
{
	char c;
	int len;

	c = read_bit(f);
	buf[0] = c;
	if (c == 0) {
		if (c == 0) {
			Term body;
			buf[1] = c;
			len = 2;
			body = get_termf(f, buf + len);
			len += body.len;
		} else if (c == 1) {
			Term l, r;
			buf[1] = c;
			len = 2;
			l = get_termf(f, buf + len);
			len += l.len;
			r = get_termf(f, buf + len);
		} else {
			fprintf(stderr, "unknown instruction");
			exit(1);
		}
	} else {
		fprintf(stderr, "unknown instruction");
		exit(1);
	}
	return (Term){
		.t = buf,
		.len = len
	};
}

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

void
run_main(char *file)
{
	Term t;
	Environment *e;
}
