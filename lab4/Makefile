PROG=lab4

SRCS = lab4.c mouse.c

CFLAGS += -pedantic
CFLAGS += -I../lab3
CFLAGS += -I../lab2

DPADD += ${LIBLCF}
LDADD += -llcf -L../lab3 -lkeyboard -L../lab2 -ltimer

.include <minix.lcom.mk>