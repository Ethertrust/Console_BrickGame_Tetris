PROGRAM_NAME = tetris

CC = gcc
CFLASG = -Wall -Wextra -Werror -std=c11
BACKEND_FILES = brick_game/tetris/*.c
FRONTEND_FILES = gui/cli/*.c
FSM_FILES = fsm_matrix/*.c
MAIN_FILE_NAME = tetris
OBJECTS_FOLDER = for_objects_files/
GAME_FOLDER = game_info
GAME_OBJ = game_info/highscore_list.txt
INSTALL_DIR = game/
DIST_FOLDER = dist
TEST_FOLDER = tests

OS = $(shell uname -s)

ifeq ($(OS),Linux)
    DOP_LIB = -lcheck -lm -lpthread -lsubunit #-lrt
else
    DOP_LIB = -lcheck -lm -lpthread
endif


all: install

$(PROGRAM_NAME).o:
	$(CC) $(CFLAGS) -c $(BACKEND_FILES) $(FRONTEND_FILES) $(FSM_FILES) 
	mkdir $(OBJECTS_FOLDER)
	mv *.o $(OBJECTS_FOLDER)

$(PROGRAM_NAME).a: clean $(PROGRAM_NAME).o 
	ar rcs $(PROGRAM_NAME).a $(OBJECTS_FOLDER)*.o
	ranlib $(PROGRAM_NAME).a

clean:
	rm -rf $(OBJECTS_FOLDER)*.o *.a $(MAIN_FILE_NAME) *.o
	rm -rf $(OBJECTS_FOLDER)
	rm -rf report
	rm -rf *.gcno *gcda *.gcov
	rm -rf testout

install: uninstall $(PROGRAM_NAME).a
	mkdir $(GAME_FOLDER)
	touch $(GAME_OBJ)
	echo "0" >> $(GAME_OBJ)
	$(CC) $(CFLAGS) -c $(MAIN_FILE_NAME).c
	mv *.o $(OBJECTS_FOLDER)
	$(CC) $(CFLAGS) -o $(PROGRAM_NAME) $(OBJECTS_FOLDER)*.o -L. $(PROGRAM_NAME).a -lm -lncurses
	mkdir $(INSTALL_DIR)
	mv $(PROGRAM_NAME) $(INSTALL_DIR)

uninstall:
	rm -rf $(GAME_FOLDER)
	rm -rf $(PROGRAM_NAME)
	rm -rf $(INSTALL_DIR)
	rm -rf $(DIST_FOLDER)
	rm -rf doxygen_folder
	rm -rf *.a

test: clean install
	$(CC) $(CFLAGS) --coverage $(BACKEND_FILES) $(TEST_FOLDER)/*.c -o testout $(DOP_LIB)
	./testout

lcov_report: test
	lcov -t "tests/s21_tetris_tests" -o tetris.info -c -d .
	genhtml -o report tetris.info
	open report/index.html
	rm -rf *.gcno *gcda *.gcov

gcov_report: test
	mkdir report
	gcovr -r. --html --html-details -o report/index.html -e tests 
	open report/index.html
	rm -rf *.gcno *gcda *.gcov

play:
	./$(INSTALL_DIR)$(MAIN_FILE_NAME)

go:	uninstall install play

dvi:
	mkdir -p doxygen_folder
	doxygen

dist: dvi dist_folder $(PROGRAM_NAME).a
	tar cf $(DIST_FOLDER)/tetris-1.0.tar $(PROGRAM_NAME).a $(OBJECTS_FOLDER) doxygen_folder

clang:
	clang-format $(FRONTEND_FILES) $(BACKEND_FILES) $(FSM_FILES) $(TEST_FOLDER)/*.c *.c -n

style:
	clang-format $(FRONTEND_FILES) $(BACKEND_FILES) $(FSM_FILES) $(TEST_FOLDER)/*.c *.c -i

dist_folder:
	mkdir -p $(DIST_FOLDER)

valgrind:
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all ./testout

cppcheck:
	cppcheck $(FRONTEND_FILES) $(BACKEND_FILES) $(FSM_FILES) $(TEST_FOLDER)/*.c *.c 