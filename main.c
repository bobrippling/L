#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "parse.h"

static const char *progname;

static void syserr(const char *fmt, ...)
{
	va_list l;
	va_start(l, fmt);
	vfprintf(stderr, fmt, l);
	va_end(l);
	fprintf(stderr, ": %s\n", strerror(errno));
	exit(1);
}

int main(int argc, char **argv)
{
	progname = argv[0];

	if(argc > 2){
		fprintf(stderr, "Usage: %s [file]\n", *argv);
		return 1;
	}

	FILE *f = argv[1] ? fopen(argv[1], "r") : stdin;
	if(!f)
		syserr("open %s", argv[1]);

	tokener *tokgen = tokenise(f);

	expr *e;
	while((e = parse(tokgen)))
		expr_print(e, stdout);

	fclose(f);

	return 0;
}
