GCC = g++ -std=c++17 -Wall -Wextra -Werror
TEST_SRC = tests/*.cpp

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    OPEN = xdg-open
endif
ifeq ($(UNAME_S),Darwin)
    OPEN = open
endif

test: clean
	$(GCC) $(TEST_SRC) -o test -lgtest
	./test

gcov_report: clean
	$(GCC) --coverage $(TEST_SRC) -o test -lgtest
	chmod +x test
	./test
	lcov -t "test" -o test.info --no-external -c -d .
	genhtml -o report/ test.info
	$(OPEN) ./report/index.html

valgrind: clean
	$(GCC) $(TEST_SRC) -o test -lgtest
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./test
	rm -rf test

clang-format:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -n */*.h */*.tpp tests/*.cpp tests/*.h *.h
	rm -f .clang-format

format:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -i */*.h */*.tpp tests/*.cpp tests/*.h *.h
	rm -f .clang-format

clean:
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf test
	rm -rf report