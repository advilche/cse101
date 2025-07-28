#------------------------------------------------------------------------------
#  Makefile for Sparse
#
#  make                     makes Sparse
#  make clean               removes all binaries
#------------------------------------------------------------------------------

MAIN		= Sparse
ADT1		= NeuralNetworks
ADT2		= Matrix
ADT3		= List

SOURCE		= $(MAIN).c
OBJECT		= $(MAIN).o

ADT1_SOURCE	= $(ADT1).c
ADT1_OBJECT = $(ADT1).o
ADT1_HEADER = $(ADT1).h

ADT2_SOURCE	= $(ADT2).c
ADT2_OBJECT = $(ADT2).o
ADT2_HEADER = $(ADT2).h

ADT3_SOURCE	= $(ADT3).c 
ADT3_OBJECT = $(ADT3).o
ADT3_HEADER = $(ADT3).h

COMPILE		= gcc -std=c17 -Wextra -Wall -c
LINK		= gcc -std=c17 -Wextra -Wall -o
REMOVE		= rm -f

$(MAIN): $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT) $(ADT3_OBJECT)
	$(LINK) $(MAIN) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT) $(ADT3_OBJECT)

$(OBJECT): $(SOURCE) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(SOURCE)

$(ADT1_OBJECT): $(ADT1_SOURCE) $(ADT1_HEADER)
	$(COMPILE) $(ADT1_SOURCE)

$(ADT2_OBJECT): $(ADT2_SOURCE) $(ADT2_HEADER)
	$(COMPILE) $(ADT2_SOURCE)

$(ADT3_OBJECT): $(ADT3_SOURCE) $(ADT3_HEADER)
	$(COMPILE) $(ADT3_SOURCE)

clean:
	$(REMOVE) $(MAIN) $(ADT1_TEST) $(ADT2_TEST)  
	$(REMOVE) $(OBJECT) $(ADT1_TEST).o $(ADT2_TEST).o $(ADT1_OBJECT) $(ADT2_OBJECT) $(ADT3_OBJECT)
