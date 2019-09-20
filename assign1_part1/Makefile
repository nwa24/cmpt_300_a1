CC = gcc #variable that is defined
CCOPTS = -c -g -Wall # set of options that are passed into the compiler
LINKOPTS = -g

# Tells us the structure of the program
# eg. make = make all
# left side is called a dependency list
# -o gives the executable name of the program

all: main

main: main.o testrunner.o smp0_tests.o
	$(CC) $(LINKOPTS) -o $@ $^

main.o: main.c smp0_tests.h
	$(CC) $(CCOPTS) -o $@ $<

testrunner.o: testrunner.c testrunner.h
	$(CC) $(CCOPTS) -o $@ $<

smp0_tests.o: smp0_tests.c testrunner.h
	$(CC) $(CCOPTS) -o $@ $<

test: main
	./main -test -f7 all

clean:
	rm -rf *.o main main.exe *~
