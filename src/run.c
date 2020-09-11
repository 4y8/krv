#include <stdio.h>
#include <stdlib.h>

#include "run.h"
#include "common.h"

#define MAX_STACK_SIZE    1000

/*
 * Instructions (by John Tromp):
 * 00 x:   lambda x
 * 01 x y: (x y)
 * 1*(n + 1) 0 : De Bruijn index n
 */

Environment *stack;
Environment *env;

static Term
get_termf(FILE *f, char *buf)
{
	char c;
	int  len;

	c          = read_bit(f);
	len        = 0;
	buf[len++] = c;
	if (c == 0) {
		c = read_bit(f);
		if (c == 0) {
			buf[len++] = c;
			Term body;
			body = get_termf(f, buf + len);
			len += body.len;
		} else if (c == 1) {
			Term l, r;
			buf[len++] = c;
			l          = get_termf(f, buf + len);
			len       += l.len;
			r          = get_termf(f, buf + len);
			len       += r.len;
		} else {
			fprintf(stderr, "unknown instruction");
			exit(1);
		}
	} else if (c == 1) {
		while ((c = read_bit(f)))
			buf[len++] = c;
		buf[len++] = c;
	} else {
		fprintf(stderr, "unknown instruction");
		exit(1);
	}
	return (Term){
		       .t   = buf,
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
	Term         t;
	Environment *e;
	char         c[1024];
	FILE *       in;

	in = fopen(file, "rb");
	if (!in) {
		printf("error: can't open file %s", file);
		exit(1);
	}
	t = get_termf(in, &c[0]);
	for (int i = 0; i < t.len; ++i)
		printf("%d\n", t.t[i]);
	fclose(in);
}
