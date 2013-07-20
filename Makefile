CC= gcc
RM= rm
SOURCES= gcli.c
OBJECTS= $(SOURCES:.c=.o)
LDFLAGS=
CFLAGS=-c -Wall

all: ${OBJECTS} 
	${CC} -o gcli.out ${OBJECTS} ${LDFLAGS}
	cp gcli.out myshell

.o: 
	${CC} ${CFLAGS} $< 

clean:
	${RM} -f *.o *.out
