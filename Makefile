# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wvla -std=c99 -pedantic -g
LDLIBS = -lcriterion

all: tinyprintf

tinyprintf: src/tinyprintf.o

test: tests/tests.o

check: testsuite
	./testsuite

testsuite: tinyprintf test
	${CC}  -o testsuite ${CFLAGS} src/tinyprintf.o tests/tests.o ${LDLIBS}


.PHONY: clean
clean:
	${RM} src/*.o tests/*.o
	${RM} testsuite

# END
