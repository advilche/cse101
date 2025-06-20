#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 6
#
#  make                     makes Arithmetic
#  make BigIntegerTest      makes BigIntegerTest
#  make ListClient          makes ListClient
#  make clean               removes all binaries
#  make ArithmeticCheck     runs Arithmetic in valgrind on in4 junk4
#  make BigIntegerCheck     runs BigIntegerTest in valgrind
#  make ListCheck           runs ListTest in valgrind
#------------------------------------------------------------------------------

MAIN           = Arithmetic
ADT1           = BigInteger
ADT2           = List
TEST           = BigIntegerTest
SOURCE         = $(MAIN).cpp
OBJECT         = $(MAIN).o
ADT1_SOURCE    = $(ADT1).cpp
ADT1_OBJECT    = $(ADT1).o
ADT1_HEADER    = $(ADT1).h
ADT2_SOURCE    = $(ADT2).cpp
ADT2_OBJECT    = $(ADT2).o
ADT2_HEADER    = $(ADT2).h
TEST_SOURCE    = $(TEST).cpp
TEST_OBJECT    = $(TEST).o
COMPILE        = g++ -std=c++17 -Wall -c
LINK           = g++ -std=c++17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

$(MAIN): $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(MAIN) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

$(TEST): $(TEST_OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(TEST) $(TEST_OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

$(OBJECT): $(SOURCE) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(SOURCE)

$(TEST_OBJECT): $(TEST_SOURCE) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(TEST_SOURCE)

$(ADT1_OBJECT): $(ADT1_SOURCE) $(ADT1_HEADER)
	$(COMPILE) $(ADT1_SOURCE)

$(ADT2_OBJECT): $(ADT2_SOURCE) $(ADT2_HEADER)
	$(COMPILE) $(ADT2_SOURCE)

clean:
	$(REMOVE) $(MAIN) $(TEST) ListClient
	$(REMOVE) $(OBJECT) $(TEST_OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

$(MAIN)Check: $(MAIN)
	$(MEMCHECK) $(MAIN) in4 junk4

$(ADT1)Check: $(TEST)
	$(MEMCHECK) $(TEST)
