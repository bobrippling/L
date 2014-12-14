#ifndef EXPR_H
#define EXPR_H

#include <stdio.h>
#include <stdbool.h>

typedef struct expr expr;

expr *expr_new_call(expr **args, size_t n);
expr *expr_new_ident(char *);
expr *expr_new_num(long long);

void expr_print(expr *, FILE *);

enum expr_kind
{
	expr_define,
	expr_lambda,

	expr_call,
	expr_ident,
	expr_num
};

void expr_recurse(expr *, void *, void fn(expr *, void *));

enum expr_kind expr_kind(expr *);

const char *expr_identifier(expr *);

#endif
