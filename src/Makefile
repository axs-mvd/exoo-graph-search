#CFLAGS = -g -pipe -W -Wall -Wno-deprecated
CFLAGS = -O3 -pipe -W -Wall -Wno-deprecated
#CFLAGS = -pipe -W -Wall -Wno-deprecated
CXXFLAGS = $(CFLAGS)

OBJECTS = exoo_helper.o LocalHistory.o exoo_tabu_search.o

EXOO_TEST_OBJECT = exoo_helper_tester.o

EXOO_MAIN_OBJECT = main.o

EXOO_TEST_EXECUTABLE = exoo_helper_tester

EXOO_MAIN_EXECUTABLE = exoo_tabu_search

ALL_EXEC = $(EXOO_MAIN_EXECUTABLE) $(EXOO_TEST_EXECUTABLE)

all: tags $(ALL_EXEC)

$(EXOO_TEST_EXECUTABLE): $(OBJECTS) $(EXOO_TEST_OBJECT) 
	$(CXX) $(CXXFLAGS) $^ -o $@

$(EXOO_MAIN_EXECUTABLE): $(OBJECTS) $(EXOO_MAIN_OBJECT)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean: clear

tags:
	ctags -R .

clear:
	rm -f *.o $(ALL_EXEC)

rebuild: clear all
