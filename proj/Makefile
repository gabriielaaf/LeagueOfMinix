PROG=proj

SRCS = main.c sprite.c champion.c animSprite.c keyboardInterpreter.c


CFLAGS += -pedantic
CFLAGS += -I../lab2
CFLAGS += -I../lab3
CFLAGS += -I../lab4
CFLAGS += -I../lab5

DPADD += ${LIBLCF}
LDADD += -L../lab5 -lvideo \
         -L../lab4 -lmouse \
         -L../lab3 -lkeyboard \
         -L../lab2 -ltimer \
         -llcf

.include <minix.lcom.mk>