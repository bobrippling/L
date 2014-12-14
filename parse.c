#include "alloc.h"
#include "token.h"

#include "parse.h"

expr *parse(tokener *tokgen)
{
	switch(token_current(tokgen)){
		case tok_eof:
			return NULL;

		case tok_ident:
			return expr_new_ident(token_ident_and_next(tokgen));

		case tok_num:
			return expr_new_num(token_num_and_next(tokgen));

		case tok_lparen:
		{
			token_next(tokgen);

			expr **args = NULL;
			size_t n = 0;
			for(;;){
				expr *sub = parse(tokgen);
				args = xrealloc(args, sizeof *args * ++n);
				args[n-1] = sub;

				switch(token_current(tokgen)){
					case tok_rparen:
						token_next(tokgen);
						goto done;

					case tok_eof:
						fprintf(stderr, "expected ')', got eof\n");
						return NULL;

					default:
						/* continue */
						;
				}
			}
done:
			return expr_new_call(args, n);
		}

		case tok_rparen:
			break;
	}

	fprintf(stderr, "expected '(' or EOF\n");
	return NULL;
}
