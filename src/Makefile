CC := g++
CFLAGS = -Wall -Werror -Wextra -std=c++17
GCOVFLAGS = -Wall -Werror -Wextra -std=c++17
GTEST_LIB := build/lib/libgtest.a
GTEST_INCLUDE := -I build/_deps/googletest-src/googletest/include

SRCS = S21_Matrix_Methods.cpp S21_Matrix_Operations.cpp S21_Matrix_overload.cpp
OBJS := $(SRCS:.cpp=.o)

all: clean test

install:
	sh install_gtest.sh

uninstall:
	rm -R build

gcov_report: s21_matrix_test.cpp s21_matrix_oop.a $(GTEST_LIB)
	$(CC) $(GCOVFLAGS) -fprofile-arcs -ftest-coverage -fPIC -o s21_matrix_test $(SRCS) s21_matrix_test.cpp -L $(GTEST_LIB) -lgtest_main -lgtest -lpthread -lgcov
	./s21_matrix_test
	mkdir gcovr-report
	gcovr -r . -e s21_matrix_test.cpp --html --html-details --output gcovr-report/coverage.html
	open gcovr-report/coverage.html
	make clean_after_run

test: s21_matrix_test.cpp s21_matrix_oop.a $(GTEST_LIB)
	$(CC) $(CFLAGS) $(GTEST_INCLUDE) -o s21_matrix_test $< s21_matrix_oop.a -L $(GTEST_LIB) -lgtest_main -lgtest -lpthread -lgcov
	./s21_matrix_test
	make clean_after_run
	
s21_matrix_oop.a: $(OBJS)
	ar rcs $@ $^

%.o: %.cpp s21_matrix_oop.h
	$(CC) $(CFLAGS) -c $< -o $@

check_clang:
	cp ../materials/linters/.clang-format .
	clang-format -n *.cpp *.h
	rm -f .clang-format

make_clang:
	cp ../materials/linters/.clang-format .
	clang-format -i *.cpp *.h
	rm -f .clang-format

valgrind: test
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes  -s ./s21_matrix_test

clean_after_run:
	rm -f $(OBJS) *.gcno *.gcov *.gcda *.info

clean_report:
	rm -R gcovr-report

clean: 
	rm -f $(OBJS) *.a s21_matrix_test *.gcno *.gcov *.gcda *.info *.html
