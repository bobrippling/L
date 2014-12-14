#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include <ctype.h>

#include "token.h"
#include "alloc.h"

struct tokener
{
	FILE *f;

	char *anchor, *pos;
	size_t anchorlen;

	enum token tok;
	bool eof;

	union
	{
		char *ident;
		long long num;
	} u;
};

tokener *tokenise(FILE *f)
{
	tokener *t = tnew(t);

	t->f = f;

	token_next(t);

	return t;
}

enum token token_current(tokener *tok)
{
	return tok->tok;
}

static char *skipspace(char *p)
{
	for(; *p && isspace(*p); p++);
	return p;
}

static char *skipident(char *p)
{
	for(; *p && !isspace(*p) && *p != '(' && *p != ')'; p++);
	return p;
}

static void tok_free_u(tokener *tok)
{
	if(tok->tok == tok_ident)
		free(tok->u.ident);
}

long long token_num_and_next(tokener *tok)
{
	long long r = tok->u.num;
	assert(tok->tok == tok_num);
	token_next(tok);
	return r;
}

char *token_ident_and_next(tokener *tok)
{
	char *ident = tok->u.ident;
	assert(tok->tok == tok_ident);
	tok->u.ident = NULL;
	token_next(tok);
	return ident;
}

static void token_next_line(tokener *tok)
{
	ssize_t n = getline(&tok->anchor, &tok->anchorlen, tok->f);

	if(n <= 0){
		tok->tok = tok_eof;
		tok->eof = true;
		return;
	}

	tok->pos = tok->anchor;
}

void token_next(tokener *tok)
{
	if(tok->tok == tok_eof && tok->eof)
		return;

	tok_free_u(tok);

	if(!tok->anchor)
		token_next_line(tok);

	tok->pos = skipspace(tok->pos);

	switch(*tok->pos){
		case '(': tok->tok = tok_lparen; tok->pos++; break;
		case ')': tok->tok = tok_rparen; tok->pos++; break;

		case '0' ... '9':
		{
			tok->tok = tok_num;

			char *end;
			tok->u.num = strtoll(tok->pos, &end, 0);
			tok->pos = end;
			break;
		}

		case '\0':
			token_next_line(tok);
			token_next(tok);
			return;

		default:
		{
			tok->tok = tok_ident;

			char *start = tok->pos;
			tok->pos = skipident(tok->pos);

			size_t len = tok->pos - start;

			tok->u.ident = xmalloc(len + 1);
			memcpy(tok->u.ident, start, len);
			tok->u.ident[len] = '\0';
			break;
		}
	}
}
