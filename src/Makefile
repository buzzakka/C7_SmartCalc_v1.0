CC = gcc
CFLAGS = -Wall -Werror -Wextra
C11 = -std=c11

all: build

build: install

s21_smart_calc: 
	$(CC) $(CFLAGS) $(C11) -g s21_*.c -o s21_smart_calc

test: clean s21_smart_calc.a
	$(CC) -fsanitize=address -lcheck test.c s21_smart_calc.a -o test.out && ./test.out

# Для корректной работы установи lcov: brew install lcov
gcov_report: coverage run_coverage lcov genhtml open

coverage:
	$(CC) --coverage test.c s21_*.c -o test -lcheck
run_coverage:
	./test
lcov:
	lcov -t "Core" -o s21_test.info -c -d .
genhtml:
	genhtml -o report s21_test.info
open:
	open ./report/index.html


s21_smart_calc.a: s21_smart_calc.o
	ar rc s21_smart_calc.a s21_*.o

s21_smart_calc.o:
	$(CC) -c $(FLAGS) s21_*.c

clean:
	rm -rf s21_smart_calc *.o *.a *.info *.gcda *.gcno *.out test report/
	cd SmartCalc && qmake && make clean && rm Makefile && rm .qmake.stash
	rm -rf Archive_SmartCalc_v1.0.tgz

install:
	@echo -------------------INSTALL-------------------
	make clean
	cd SmartCalc && qmake && make && make clean && rm Makefile && mkdir build && mv SmartCalc.app/Contents/MacOS/SmartCalc build/

uninstall:
	@echo -------------------UNINSTALL-------------------
	cd SmartCalc/ && rm -rf build

dist:
	@echo -------------------DIST-------------------
	rm -rf Archive_SmartCalc_v1.0/
	mkdir Archive_SmartCalc_v1.0/
	cp SmartCalc/build/SmartCalc Archive_SmartCalc_v1.0/
	tar cvzf Archive_SmartCalc_v1.0.tgz ./Archive_SmartCalc_v1.0
	rm -rf Archive_SmartCalc_v1.0

open_calc:
	open SmartCalc/build/SmartCalc.app

dvi:
	open readme.html

rebuild: clean uninstall build

style:
	@echo -------------------STYLE_TEST-------------------
	cp ../materials/linters/.clang-format ./
	clang-format -n *.c *h
	rm -rf .clang-format

leaks:
	@echo -------------------MEMORY_LEAKS-------------------
	$(CC) -g *.c -lcheck -o unit.out
	CK_FORK=no leaks --atExit -- ./unit.out
	rm -rf unit.out