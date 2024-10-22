CC = gcc
#CFLAGS = -Wall -Wextra -Werror -std=c11 -fsanitize=undefined
CFLAGS = -Wall -Wextra -Werror -std=c11
BIN_DIR = ../build/
BIN = $(BIN_DIR)graph
LEX_TEST = $(BIN_DIR)lex_test
STACK_TEST = $(BIN_DIR)stack_test

all: graph	
	$(BIN)

graph: graph.c func.c stack.c lex.c stack_lex.c
	$(CC) $(CFLAGS) $^ -o $(BIN)
	$(BIN)

lex_test: lex.c lex_test.c stack_lex.c
	$(CC) $(CFLAGS) $^ -o $(LEX_TEST)
	$(LEX_TEST)
#	leaks --atExit -- $(LEX_TEST)

lex_test_input: lex.c lex_test.c stack_lex.c
	$(CC) $(CFLAGS) $^ -o $(LEX_TEST) -D TEST_INPUT
	$(LEX_TEST)

stack_lex_test: stack_lex.c stack_lex_test.c
	$(CC) $(CFLAGS) $^ -o $(STACK_TEST)
	leaks --atExit -- $(STACK_TEST)
	
clean:
	rm -rf *.out $(BIN)

clean_all:
	rm -rf *.out $(BIN) $(LEX_TEST) $(STACK_TEST)

rebuild: clean all		

.PHONY: all clean clean_all lex_test stack_test 