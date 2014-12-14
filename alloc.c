#include <stdlib.h>
#include <string.h>

#include "alloc.h"

void *xrealloc(void *p, size_t l)
{
	void *new = realloc(p, l);
	if(!new)
		abort();
	return new;
}

void *xmalloc(size_t l)
{
	void *p = malloc(l);
	if(!p)
		abort();
	memset(p, 0, l);
	return p;
}

char *xstrdup(const char *s)
{
	size_t l = strlen(s);
	char *r = xmalloc(l + 1);
	memcpy(r, s, l + 1);
	return r;
}
