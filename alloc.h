#ifndef ALLOC_H
#define ALLOC_H

#include <stddef.h>

void *xrealloc(void *, size_t);

void *xmalloc(size_t);

char *xstrdup(const char *);

#ifdef __GNUC__
#  define tnew(exp) (__typeof(exp))xmalloc(sizeof*(exp))
#else
#  define tnew(exp) xmalloc(sizeof(exp))
#endif

#endif
