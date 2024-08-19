CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra
SRC = source/*.c
TEST_SRC = tests/*.c
LIBSFLAGS = -lcheck -lm -lsubunit
GCOV_FLAGS = --coverage

LIB = s21_matrix.a
GCOVR_PATH =~/.local/bin/gcovr
# GCOVR_PATH=/usr/bin/gcovr
REPORT = report/index.html

all: s21_matrix.a

s21_matrix.a:
	$(CC) $(CFLAGS) -c $(SRC)
	ar rc $(LIB) *.o
	ranlib $(LIB)

test: s21_matrix.a
	$(CC) $(CFLAGS) -L. -l:$(LIB) $(SRC) ${TEST_SRC} -o test_result $(LIBSFLAGS)
	./test_result

test_gcov: s21_matrix.a
	$(CC) $(CFLAGS) -L. -l:$(LIB) $(SRC) ${TEST_SRC} -o test_result $(LIBSFLAGS) $(GCOV_FLAGS)
	./test_result

gcov_report: test_gcov
	mkdir -p report
	${GCOVR_PATH} -r . --html --html-details -o $(REPORT) -e ${TEST_SRC}
	xdg-open $(REPORT)

clean:
	rm -rf test_result
	rm -rf report
	rm -rf *.gcno
	rm -rf *.gcda
	rm -rf *.o
	rm -rf debug_result
	rm -rf $(LIB)

clang:
	cp ../materials/linters/.clang-format source/
	cp ../materials/linters/.clang-format tests/
	cp ../materials/linters/.clang-format .
	clang-format -n source/*.c
	clang-format -n tests/*.c
	clang-format -n s21_matrix.h
	clang-format -i s21_matrix.h
	clang-format -i tests/*.c
	clang-format -i source/*.c
	rm .clang-format
	rm tests/.clang-format
	rm source/.clang-format

valgrind: test
	valgrind --tool=memcheck --leak-check=yes ./test_result
