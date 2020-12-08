.PHONY: all clean

all: test

test: logger.o main.o
	gcc -o $@ $?

main.o: main.c
	gcc -c $?

logger.o: logger.c
	gcc -c $?

clean:
	rm test *.o
