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
SVG=svg

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

$(LIB)/libBRD.a: $(OBJ)/libASCII.o $(OBJ)/BRDnode.o $(OBJ)/BRDtree.o $(OBJ)/ListWord.o $(OBJ)/BRDerrno.o $(OBJ)/BRD_API.o $(OBJ)/BRD_TermView.o $(OBJ)/BRD_SVGView.o $(OBJ)/AverageDepth.o
	$(AR) $@ $^
	ranlib $@

$(LIB)/libTRH.a: $(OBJ)/libASCII.o $(OBJ)/TRHnode.o $(OBJ)/TRHtree.o $(OBJ)/ListWord.o $(OBJ)/TRH_API.o $(OBJ)/AverageDepth.o $(OBJ)/TRH_View.o
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

# Unit test 2 :
$(BIN)/unit_test_2: $(OBJ)/unit_test_2.o $(LIB)/libBRD.a
	$(CC) -o $@ $< -L$(LIB) -lBRD
unit_test_2: $(BIN)/unit_test_2
run_unit_test_2: $(BIN)/unit_test_2
	$(BIN)/unit_test_2

# Unit test 3 :
$(BIN)/unit_test_3: $(OBJ)/unit_test_3.o $(LIB)/libBRD.a
	$(CC) -o $@ $< -L$(LIB) -lBRD
unit_test_3: $(BIN)/unit_test_3
run_unit_test_3: $(BIN)/unit_test_3
	$(BIN)/unit_test_3

# TRH_unit_test :
$(BIN)/TRH_unit_test: $(OBJ)/TRH_unit_test.o $(LIB)/libTRH.a
	$(CC) -o $@ $< -L$(LIB) -lTRH
TRH_unit_test: $(BIN)/TRH_unit_test
run_TRH_unit_test: $(BIN)/TRH_unit_test
	$(BIN)/TRH_unit_test


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
	rm -rf $(LIB) $(BIN) $(OBJ);
	echo "" > $(SVG)/BRD.svg
