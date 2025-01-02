GCC = g++ -Wall -Wextra -Werror -std=c++17 -g  
GCOVFLAGS = -fprofile-arcs -ftest-coverage  
UNAME := $(shell uname -s)  
ifeq ($(UNAME),Linux)  
LINK_FLAGS= -lsubunit -lrt -lm -lpthread  
   
endif  
ifeq ($(UNAME),Darwin)  
GCOVIOS=--ignore-error inconsistent 
endif  
 
all: test 
 
test: 
	$(GCC) all_tests/*.cc  $(LINK_FLAGS) -o test -lgtest 
	./test  
 
gcov_report: 
	$(GCC) $(GCOVFLAGS) all_tests/*.cc */*.h -L. -o test -lgtest $(LINK_FLAGS) 
	./test  
	lcov $(GCOVIOS) -t test  -o test.info -c -d .  
	genhtml -o report test.info 
	open report/index.html 
 
 
format: 
	clang-format -style=google -i all_tests/*.cc vector/*.h array/*.h list/*.h map/*.h queue/*.h set/*.h tree/*.h stack/*.h *.h 
 
style: 
	clang-format -style=google -n all_tests/*.cc vector/*.h array/*.h list/*.h map/*.h queue/*.h set/*.h tree/*.h stack/*.h *.h 
 
clean: 
	rm -rf *.o 
	rm -rf *.a 
	rm -rf test 
	rm -rf *.gcda *.gcno 
	rm -rf report 
	rm -rf *.gcov 
	rm -rf *.info 
 
rebuild: clean all	
