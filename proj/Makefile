PROG=proj

.PATH: ${.CURDIR}/controller \
       ${.CURDIR}/input \
       ${.CURDIR}/model \
       ${.CURDIR}/model/champion \
       ${.CURDIR}/model/minion \
       ${.CURDIR}/model/state \
       ${.CURDIR}/viewer \
       ${.CURDIR}/viewer/sprite

SRCS = main.c \
       ChampionController.c \
       Controller.c \
       GameController.c \
       MinionController.c \
       KeyboardInterpreter.c \
       MouseInterpreter.c \
       TimerInterpreter.c \
       Box.c \
       Position.c \
       Champion.c \
       Minion.c \
       GameState.c \
       State.c \
       AnimSprite.c \
       BuildSprites.c \
       Sprite.c \
       ChampionViewer.c \
       GameViewer.c \
       MinionViewer.c \
       Viewer.c

CFLAGS += -pedantic
CFLAGS += -I${.CURDIR}/../lab2
CFLAGS += -I${.CURDIR}/../lab3
CFLAGS += -I${.CURDIR}/../lab4
CFLAGS += -I${.CURDIR}/../lab5

DPADD += ${LIBLCF}
LDADD += -llcf \
    -L${.CURDIR}/../lab5 -lvideo \
    -L${.CURDIR}/../lab4 -lmouse \
    -L${.CURDIR}/../lab3 -lkeyboard \
    -L${.CURDIR}/../lab2 -ltimer

.include <minix.lcom.mk>
