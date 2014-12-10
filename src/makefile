################################################################################
# ALGAV makefile
# 
# @Version 2.0
# @author Ilyas Toumlilt, Amin Affes
#
################################################################################

CC=gcc -Wall -ansi
AR=ar crv

LPTHREAD=-lpthread

SRC=src
LIB=lib
INC=include
OBJ=obj
BIN=bin

all: directories libBRD libTRH

################################################################################
# Directories
################################################################################

directories: $(OBJ) $(BIN) $(LIB)

$(OBJ):
	mkdir $(OBJ)

$(BIN):
	mkdir $(BIN)

$(LIB):
	mkdir $(LIB)

################################################################################
# Default gen
################################################################################

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -c -o $@ $< -I$(INC) 

$(BIN)/% : $(OBJ)/%.o
	$(CC) -o $@ $< $(LPTHREAD)

################################################################################
# Libraries
################################################################################

libBRD: $(LIB)/libBRD.a
libTRH: $(LIB)/libTRH.a

$(LIB)/libBRD.a: $(OBJ)/libASCII.o $(OBJ)/BRDnode.o $(OBJ)/BRDtree.o $(OBJ)/ListWord.o $(OBJ)/BRDerrno.o $(OBJ)/BRD_API.o $(OBJ)/BRD_TermView.o $(OBJ)/BRD_SVGView.o
	$(AR) $@ $^
	ranlib $@

$(LIB)/libTRH.a: $(OBJ)/libASCII.o $(OBJ)/TRHnode.o $(OBJ)/TRHtree.o $(OBJ)/ListWord.o $(OBJ)/BRD_API.o
	$(AR) $@ $^
	ranlib $@

################################################################################
# Other dependencies
################################################################################


################################################################################
# Unit tests
################################################################################

# Unit test 1 :
$(BIN)/unit_test_1: $(OBJ)/unit_test_1.o $(LIB)/libBRD.a
	$(CC) -o $@ $< -L$(LIB) -lBRD
unit_test_1: $(BIN)/unit_test_1
run_unit_test_1: $(BIN)/unit_test_1
	$(BIN)/unit_test_1

################################################################################
# View graphs
################################################################################

# BRD graph
BRDview :
	@inkscape svg/BRD.svg 2>/dev/null 

################################################################################
# clean repository
################################################################################
clean:
	rm -rf $(LIB) $(BIN) $(OBJ)