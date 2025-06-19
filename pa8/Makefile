#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 8
#
#  make WordFrequency      compiles the WordFrequency executable
#  make Order              compiles the Order executable
#  make DictionaryClient   compiles the DictionaryClient executable
#  make DictionaryTest     compiles the DictionaryTest executable
#  make clean              removes all binaries
#------------------------------------------------------------------------------

# Variables
ADT            = Dictionary
ADT_SOURCE     = $(ADT).cpp
ADT_OBJECT     = $(ADT).o
ADT_HEADER     = $(ADT).h
COMPILE        = g++ -std=c++17 -Wall -c
LINK           = g++ -std=c++17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

# WordFrequency Variables
MAIN_WF        = WordFrequency
WF_SOURCE      = $(MAIN_WF).cpp
WF_OBJECT      = $(MAIN_WF).o

# Order Variables
MAIN_ORDER     = Order
ORDER_SOURCE   = $(MAIN_ORDER).cpp
ORDER_OBJECT   = $(MAIN_ORDER).o

# DictionaryClient Variables
MAIN_CLIENT    = DictionaryClient
CLIENT_SOURCE  = $(MAIN_CLIENT).cpp
CLIENT_OBJECT  = $(MAIN_CLIENT).o

# DictionaryTest Variables
MAIN_TEST      = DictionaryTest
TEST_SOURCE    = $(MAIN_TEST).cpp
TEST_OBJECT    = $(MAIN_TEST).o

# Targets to make each client

# Compiles and links WordFrequency executable
$(MAIN_WF): $(WF_OBJECT) $(ADT_OBJECT)
	$(LINK) $(MAIN_WF) $(WF_OBJECT) $(ADT_OBJECT)

# Compiles and links Order executable
$(MAIN_ORDER): $(ORDER_OBJECT) $(ADT_OBJECT)
	$(LINK) $(MAIN_ORDER) $(ORDER_OBJECT) $(ADT_OBJECT)

# Compiles and links DictionaryClient executable
$(MAIN_CLIENT): $(CLIENT_OBJECT) $(ADT_OBJECT)
	$(LINK) $(MAIN_CLIENT) $(CLIENT_OBJECT) $(ADT_OBJECT)

# Compiles and links DictionaryTest executable
$(MAIN_TEST): $(TEST_OBJECT) $(ADT_OBJECT)
	$(LINK) $(MAIN_TEST) $(TEST_OBJECT) $(ADT_OBJECT)

# Compile the individual object files

# Compiles WordFrequency.o from WordFrequency.cpp
$(WF_OBJECT): $(WF_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(WF_SOURCE)

# Compiles Order.o from Order.cpp
$(ORDER_OBJECT): $(ORDER_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ORDER_SOURCE)

# Compiles DictionaryClient.o from DictionaryClient.cpp
$(CLIENT_OBJECT): $(CLIENT_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(CLIENT_SOURCE)

# Compiles DictionaryTest.o from DictionaryTest.cpp
$(TEST_OBJECT): $(TEST_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(TEST_SOURCE)

# Compiles Dictionary.o from Dictionary.cpp
$(ADT_OBJECT): $(ADT_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ADT_SOURCE)

# Clean command to remove all object files and executables
clean:
	$(REMOVE) $(MAIN_WF) $(MAIN_ORDER) $(MAIN_CLIENT) $(MAIN_TEST) \
	$(WF_OBJECT) $(ORDER_OBJECT) $(CLIENT_OBJECT) $(TEST_OBJECT) $(ADT_OBJECT)

# Memcheck commands for valgrind testing

# Runs valgrind on WordFrequency using Gutenberg input
$(MAIN_WF)Check: $(MAIN_WF)
	$(MEMCHECK) ./$(MAIN_WF) Gutenberg myGutenberg-out

# Runs valgrind on DictionaryClient
$(MAIN_CLIENT)Check: $(MAIN_CLIENT)
	$(MEMCHECK) ./$(MAIN_CLIENT)

# Runs valgrind on DictionaryTest
$(MAIN_TEST)Check: $(MAIN_TEST)
	$(MEMCHECK) ./$(MAIN_TEST)

