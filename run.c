#include <stdio.h>

#include "dynmap.h"

#include "run.h"

/* char * => expr * */
typedef dynmap symtable;

void link_idents(expr *e, symtable *symtab)
{
	switch(expr_kind(e)){
		case expr_define:
		{
			const char *sp = expr_identifier(e); // e[0] ?

			expr *old = dynmap_set(const char *, expr *, symtab, sp, e);
			if(old)
				fprintf(stderr, "redefining %s\n", sp);
		}

		case expr_lambda:
			fprintf(stderr, "TODO: lambda\n");

		case expr_num:
		case expr_call:
			break;

		case expr_ident:
		{
			const char *ident = expr_identifier(e);
			expr *def = dynmap_get(const char *, expr *, symtab, ident);
			if(def)
				expr_set_extra(e, def);
			else
				fprintf(stderr, "couldn't find %s\n", ident);
			break;
		}
	}
}

void run_expr(expr *e)
{
	symtable *symtab = dynmap_new(const char *, NULL, dynmap_strhash);

	expr_recurse(e, symtab, (void (*)(expr *, void *))link_idents);

	dynmap_free(symtab);
}
