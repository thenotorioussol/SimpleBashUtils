CC= gcc -std=c11
CFLAGS= -Wall -Wextra -Werror
CAT= s21_cat.c

all: s21_cat

s21_cat:
	$(CC) $(CFLAGS) $(CAT) -o s21_cat

test:
	chmod 777 test.sh
	./test.sh

clean:
	rm -rf s21_cat
	rm -rf *.a *.out *.o *.txt

check:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	python3 ../../materials/linters/cpplint.py --extensions=c *.c *.h
	valgrind ./s21_cat

rebuild:
	make clean
	make all
	rm -rf  *.o *.a
	