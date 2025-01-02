RES_DIR = resourses
DOC_DIR = doc
BUILD_DIR = build
INSTALL_DIR = install
CC := g++
CFLAGS := -std=c++17 -Wall -Werror -Wextra
PROJECT_NAME := CPP4_3DViewer_v2.0-1


all: install

res:
	mkdir -p $(RES_DIR)

s21_object.a: res
	$(CC) $(CFLAGS) -c backend/*.cc controller/*.cc
	mv *.o $(RES_DIR)/
	ar rcs s21_object.a $(RES_DIR)/object.o $(RES_DIR)/s21_matrix.o $(RES_DIR)/affine.o $(RES_DIR)/model.o $(RES_DIR)/controller.o
	ranlib s21_object.a


install: uninstall s21_object.a
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ../ && make
	mkdir -p $(INSTALL_DIR)
	mv $(BUILD_DIR)/s21_3d_viewer $(INSTALL_DIR)
ifeq ($(shell uname), Linux)
	chmod 0700 /run/user/1000 
endif

clean:
	rm -rf $(DOC_DIR) $(RES_DIR) $(BUILD_DIR) *.o *.a s21_3d_viewer

uninstall: clean
	rm -rf $(INSTALL_DIR)

dvi:
	mkdir -p $(DOC_DIR)
	doxygen Doxyfile

dist:
	zip -r ../../$(PROJECT_NAME).zip ../../$(PROJECT_NAME)

vg:
	valgrind  --tool=memcheck --track-fds=yes --trace-children=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./install/s21_3d_viewer

tests: clean s21_object.a
	$(CC) $(CFLAGS) test/test.cc test/model.cc -L. s21_object.a -o s21_3d_viewer -lgtest
	./s21_3d_viewer

clang:
	 cp ../materials/linters/.clang-format ./
	 clang-format -i *.h *.cc view/* controller/* backend/*
	 rm .clang-format

