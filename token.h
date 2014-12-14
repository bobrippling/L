#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>

typedef struct tokener tokener;
tokener *tokenise(FILE *);

enum token
{
	tok_eof,
	tok_lparen,
	tok_rparen,
	tok_ident,
	tok_num
};

enum token token_current(tokener *);
void token_next(tokener *);

long long token_num_and_next(tokener *);
char *token_ident_and_next(tokener *);

#endif
