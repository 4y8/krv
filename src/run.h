typedef char *Term;

typedef struct clo {
	Term        t;
	struct env *e;
} Closure;

typedef struct env {
	int      top;
	Closure *c;
} Environment;

static Term mkterm(char *);
static Closure mkclosure(Term, Environment);
static Environment mkenv(void);
static void push(Term, Environment, Environment *);
