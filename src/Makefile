CC=g++
FLAGS=-Wall -Wextra -Werror -std=c++17
LINK_FLAGS = -lgtest -lgtest_main -pthread 
TEST=tests/*.cc
LIB_NAME=s21_list_oop.a
UNAME_S := $(shell uname -s)

all: clean test

test: clean
	$(CC) $(FLAGS) $(TEST) ${LINK_FLAGS} -o test -lgtest
	./test

leaks: test
ifeq ($(UNAME_S), Linux) 
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test
endif
ifeq ($(UNAME_S), Darwin) 
	leaks -quiet -atExit -- ./test
endif

gcov_flag:
	$(eval FLAGS += -fprofile-arcs -ftest-coverage)

gcov_report: gcov_flag test
	gcov --no-output $(TEST)
	lcov --no-external --capture --directory . --output-file coverage.info
	genhtml coverage.info -o report
	open report/index.html	


clean:
	rm -f *.o *.a test *.gcda *.gcno *.info
	rm -rf report

clang-format:
	cp ../materials/linters/.clang-format .
	clang-format -style=google -i Sorted_Container/*.h  Sorted_Container/Associative_Container/associatice_container.h Sorted_Container/Associative_Container/map_dir/*.h Sorted_Container/RBtree/*.h Sorted_Container/Set_Container/*.h Sorted_Container/Set_Container/Multiset_dir/s21_multiset.h Sorted_Container/Set_Container/set_dir/s21_set.h
	clang-format -style=google -i Sequence_Container/sequence_container.h Sequence_Container/list_dir/s21_list.h Sequence_Container/deque_dir/s21_deque.h
	clang-format -style=google -i Additional_Container/additional_container.h Additional_Container/array_dir/s21_array.h
	clang-format -style=google -i Adaptor_Container/adaptor_container.h Adaptor_Container/queue_dir/s21_queue.h Adaptor_Container/Stack_dir/s21_stack.h
	clang-format -style=google -i Sequence_Container/vector_dir/vector.h Sequence_Container/vector_dir/vector_container.h Sequence_Container/vector_dir/s21_vector.h Sequence_Container/vector_dir/vector/constructors_and_destructor.cpp Sequence_Container/vector_dir/vector/functions.cpp Sequence_Container/vector_dir/vector/methods.cpp Sequence_Container/vector_dir/vector/operators.cpp 
	clang-format -style=google -i tests/*.cc 
	rm .clang-format

