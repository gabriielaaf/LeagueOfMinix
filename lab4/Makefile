PROG=lab4

SRCS = lab4.c mouse.c

CFLAGS += -pedantic
CFLAGS += -I../lab3
CFLAGS += -I../lab2

DPADD += ${LIBLCF}
LDADD += -llcf -L../lab3 -lkeyboard -L../lab2 -ltimer

LIB_NAME = libmouse.a
LIB_SRCS = mouse.c
LIB_OBJS = ${LIB_SRCS:.c=.o}
CLEANFILES += ${LIB_NAME} ${LIB_OBJS}

all: lib

lib: ${LIB_OBJS}
	ar rcs ${LIB_NAME} ${LIB_OBJS}

.include <minix.lcom.mk>