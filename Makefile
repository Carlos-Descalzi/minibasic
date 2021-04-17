CC=gcc
LD=gcc
CFLAGS=-Wall -g
LDFLAGS=
OBJS=main.o scanner.o strings.o parser.o memory.o variables.o program.o keywords.o stack.o eval.o console_linux.o

all: mbasic

mbasic: $(OBJS)
	$(LD) -o mbasic $(OBJS) $(LDFLAGS)

.o: .c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf mbasic *.o
