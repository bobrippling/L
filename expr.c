#include "alloc.h"

#include "expr.h"

struct expr
{
	enum expr_kind
	{
		CALL,
		IDENT,
		NUM
	} type;
	struct
	{
		struct
		{
			expr **es;
			size_t n;
		} args;
		char *ident;
		long long num;
	} u;
};

static expr *expr_new(enum expr_kind k)
{
	expr *e = tnew(e);
	e->type = k;
	return e;
}

expr *expr_new_call(expr **args, size_t n)
{
	expr *e = expr_new(CALL);
	e->u.args.es = args;
	e->u.args.n = n;
	return e;
}

expr *expr_new_ident(char *ident)
{
	expr *e = expr_new(IDENT);
	e->u.ident = xstrdup(ident);
	return e;
}

expr *expr_new_num(long long l)
{
	expr *e = expr_new(NUM);
	e->u.num = l;
	return e;
}

static void expr_print_indent(expr *e, FILE *f, size_t indent)
{
	for(size_t i = indent; i > 0; i--)
		fputc('\t', f);

	switch(e->type){
		case CALL:
			fprintf(f, "call:\n");
			for(size_t i = 0; i < e->u.args.n; i++)
				expr_print_indent(e->u.args.es[i], f, indent + 1);
			break;

		case IDENT:
			fprintf(f, "ident %s\n", e->u.ident);
			break;

		case NUM:
			fprintf(f, "num %lld\n", e->u.num);
			break;
	}
}

void expr_print(expr *e, FILE *f)
{
	expr_print_indent(e, f, 0);
}
