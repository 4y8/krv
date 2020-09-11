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

Closure stack_clo[MAX_STACK_SIZE];
Closure env_clo[MAX_STACK_SIZE];

Environment stack = {
	.top =             0,
	.c   = &stack_clo[0],
};
Environment env = {
	.top =           0,
	.c   = &env_clo[0],
};

static Term
get_termt(char *t)
{
	char c;
	int  len;

	len = 0;
	c   = t[len++];
	if (c == 0) {
		c = t[len++];
		if (c == 0) {
			Term body;
			body = get_termt(t + len);
			len += body.len;
		} else if (c == 1) {
			Term l, r;
			l    = get_termt(t + len);
			len += l.len;
			r    = get_termt(t + len);
			len += r.len;
		} else {
			fprintf(stderr, "unknown instruction");
			exit(1);
		}
	} else if (c == 1)
		while ((c = t[len++]) == 1);
	else {
		fprintf(stderr, "unknown instruction");
		exit(1);
	}
	return (Term){
		       .t   = t,
		       .len = len,
		       .pos = 0
	};
}

static Term
get_termf(FILE *f, char *buf)
{
	int len;

	len = 0;
	while ((buf[len++] = read_bit(f)) != -1);
	return get_termt(buf);
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
	push(mkclosure(r, e), &stack);
	eval(l, e);
}

static void
lam(Term t, Environment *e)
{
	push(pop(&stack), e);
	eval(t, e);
}

static void
deb(int n, Environment *e)
{
	Closure c;

	for (; n > 0; --n) (void)pop(e);
	c = pop(e);
	eval(c.t, c.e);
}

static void
eval(Term t, Environment *e)
{
	if (t.t[t.pos] == 0) {
		if (t.t[t.pos + 1] == 0) {
			t.pos += 2;
			lam(t, e);
		}
		else {
			Term l, r;
			l = get_termt(t.t + t.pos + 2);
			r = get_termt(t.t + t.pos + l.len + 2);
			app(l, r, e);
		}
	} else {
		int n;
		n = 0;
		while (t.t[t.pos + (n++)]);
		deb(n, e);
	}
}

void
run_main(char *file)
{
	Term  t;
	char  c[1024];
	FILE *in;

	in = fopen(file, "rb");
	if (!in) {
		printf("error: can't open file %s", file);
		exit(1);
	}
	t = get_termf(in, &c[0]);
	for (int i = 0; i < t.len; ++i)
		printf("%d\n", t.t[i]);
	eval(t, &env);
	fclose(in);
}
