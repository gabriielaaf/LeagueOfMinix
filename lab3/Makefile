PROG=lab3

SRCS = lab3.c keyboard.c utils.c

CFLAGS += -pedantic
CFLAGS += -I../lab2

DPADD += ${LIBLCF}
LDADD += -llcf -L../lab2 -ltimer

.include <minix.lcom.mk>