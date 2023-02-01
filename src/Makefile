UNAME:=$(shell uname -s)
ifeq ($(UNAME),Linux)
	LFLAGS=-lcheck -lsubunit -lrt -lm -lpthread
	LEAK=valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file="leak.log"
endif
ifeq ($(UNAME),Darwin)
	LFLAGS=-lcheck -lm
	LEAK=leaks -quiet -atExit --
endif
CCFLAGS=-Wall -Werror -Wextra -std=c11
GFLAGS=-fprofile-arcs -ftest-coverage
SOURCES=CalcFiles/calc_polish_notation_module.c CalcFiles/calc.c CalcFiles/alib_dynamic_module.c CalcFiles/read_term_module.c CalcFiles/transfer_to_polish_notation.c

all: clean s21_calc gcov_report dist clean

style:
	clang-format -n CalcFiles/*.c CalcFiles/*.h QCfiles/*.cpp QCfiles/*.h *.c

style_force:
	clang-format -i CalcFiles/*.c CalcFiles/*.h QCfiles/*.cpp QCfiles/*.h

s21_calc: clean
	gcc $(CFLAGS) -c $(SOURCES)
	ar rc s21_calc.a *.o
	ranlib s21_calc.a
	rm -f *.o

build: clean
	mkdir ../build/
	cp Calcul.pro ../build/
	cd ../build/; qmake Calcul.pro
	make -C ../build/

install: build dvi
	mkdir SmartCalc
	cp -rf ../build/Calcul.app SmartCalc
	mv dociment.pdf SmartCalc/
	make clean

uninstall:
	rm -rf SmartCalc

dvi:
	pdflatex dociment.tex

dist: uninstall install
	tar -zcvf Calc_Archive.tar SmartCalc

gcov_report: clean
	gcc $(GFLAGS) $(CFLAGS) $(SOURCES) test.c $(LFLAGS) -o test
	-./test > test.log
	bash test_log.sh
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html
	
test: s21_calc
	gcc $(CFLAGS) test.c s21_calc.a -L. $(LFLAGS) -o test
	-./test > test.log
	bash test_log.sh

leaks: s21_calc
	gcc $(CFLAGS) test.c s21_calc.a -L. $(LFLAGS) -o test
	CK_FORK=no $(LEAK) ./test > leak.log
	bash test_leak.sh

rebuild: clean gcov_report

clean:
	rm -f test s21_calcul.a *.gc* test.info log.xml test.log leak.log s21_calc.a
	rm -f -rf report
	rm -f dociment.aux dociment.log dociment.pdf dociment.out
	rm -rf ../build
