CC= gcc
RM= rm
SOURCES= gcli.c stacktrace.c
OBJECTS= $(SOURCES:.c=.o)
LDFLAGS=
CFLAGS=-c -Wall

all: ${OBJECTS} 
	${CC} -o gcli ${OBJECTS} ${LDFLAGS}
	cp gcli myshell
	./gcli

.o: 
	${CC} ${CFLAGS} $< 

clean:
	${RM} -f *.o *.out
