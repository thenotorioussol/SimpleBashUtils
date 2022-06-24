CC= gcc -std=c11
CFLAGS= -Wall -Wextra -Werror
GREP= s21_grep.c

all: s21_grep

s21_grep:
	$(CC) $(CFLAGS) $(GREP) -o s21_grep

test:
	chmod 777 test.sh
	./test.sh

clean:
	rm -rf s21_grep
	rm -rf *.a *.out *.o *.txt

check:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	python3 ../../materials/linters/cpplint.py --extensions=c *.c *.h
	valgrind ./s21_grep

rebuild:
	make clean
	make all
	rm -rf  *.o *.a
