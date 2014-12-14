#ifndef EXPR_H
#define EXPR_H

#include <stdio.h>

typedef struct expr expr;

expr *expr_new_call(expr **args, size_t n);
expr *expr_new_ident(char *);
expr *expr_new_num(long long);

void expr_print(expr *, FILE *);

#endif
