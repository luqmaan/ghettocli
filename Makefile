# Joseph Fields U8254-5313, and Luq U
# Operating Systems Project - Summer 2013

CC= gcc
RM= rm
SOURCES= clear.c dir.c echo.c exec.c help.c more.c pause.c quit.c stacktrace.c curse.c myshell.c
OBJECTS= $(SOURCES:.c=.o)
LDFLAGS=-lncurses
CFLAGS=-c -Wall -DCURSES=1 -DSTACKTRACE=1

# To disable curses and/or stacktrace, use following
#CFLAGS=-c -Wall
#LDFLAGS=

all: ${OBJECTS} 
	${CC} -o gcli ${OBJECTS} ${LDFLAGS}

.o: 
	${CC} ${CFLAGS} $< 

clean:
	${RM} -f *.o gcli


tests: tests_dir tests_more

tests_dir:
	echo "TEST: dir.c =============="
	cd tests && gcc -wall -o dir.out ../dir.c dir.c && ./dir.out

tests_more:
	echo "TEST: more.c =============="
	cd tests && gcc -wall -o more.out ../more.c more.c && ./more.out


