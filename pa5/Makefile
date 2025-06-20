#------------------------------------------------------------------------------
#  Makefile for List ADT
#
#  make                makes ListTest
#  make ListTest       makes ListTest (your test program)
#  make clean          removes binary files
#  make check1         runs valgrind on ListTest
#  make check2         runs valgrind on Shuffle with CLA 35
#------------------------------------------------------------------------------

# Target to build the ListTest program
ListTest : ListTest.o List.o
	g++ -std=c++17 -Wall -o ListTest ListTest.o List.o 

# Compile ListTest.cpp into an object file
ListTest.o : List.h ListTest.cpp
	g++ -std=c++17 -Wall -c ListTest.cpp

# Compile List.cpp into an object file (already included in your original Makefile)
List.o : List.h List.cpp
	g++ -std=c++17 -Wall -c List.cpp

# Clean up generated files
clean :
	rm -f ListTest ListTest.o Shuffle Shuffle.o ListClient ListClient.o List.o

# Check memory leaks for ListTest using valgrind
check1 : ListTest
	valgrind --leak-check=full ListTest

# Check memory leaks for Shuffle using valgrind (original rule)
check2 : Shuffle
	valgrind --leak-check=full Shuffle 35
