CPPFLAGS = -D_XOPEN_SOURCE=700
CFLAGS = -std=c99 -g
LDFLAGS = -g

SRC = alloc.c main.c parse.c token.c expr.c run.c dynmap.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

l: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f ${OBJ} ${DEP} l

%.d: %.c
	${CC} ${CFLAGS} -MF$@ -MM -MT$@ -MT${<:.c=.o} $<

-include ${DEP}
