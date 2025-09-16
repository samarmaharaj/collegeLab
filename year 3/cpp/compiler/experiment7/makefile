CC = gcc
CFLAGS = -Wno-implicit-function-declaration

all: grammar_checker

grammar_checker: checker.tab.o checker.lex.o
	$(CC) $(CFLAGS) -o $@ $^ -lfl

checker.tab.c checker.tab.h: checker.y
	bison -d -v checker.y

checker.lex.c: checker.l checker.tab.h
	flex -o checker.lex.c checker.l

checker.tab.o: checker.tab.c
	$(CC) $(CFLAGS) -c $<

checker.lex.o: checker.lex.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f grammar_checker *.o checker.lex.c checker.tab.c checker.tab.h *.output
