# File: Makefile
# Name: Daniel Grew - 0978547
# Description: This is the make file which compiles all components of the assignment 

# macros 
INC = inc/
SRC = src/
BIN = bin/

CC = gcc 
CFLAGS = -Wall -std=c11 -g


all: $(BIN)assignment3

$(BIN)assignment3: $(BIN)main.o $(BIN)P11.o $(BIN)P12.o $(BIN)P21.o $(BIN)P22.o $(BIN)P23.o $(BIN)filehandler.o 
	$(CC) $(CFLAGS) -L$(BIN) $(BIN)*.o -o $(BIN)assignment3 -lm

$(BIN)main.o: $(SRC)main.c $(INC)assignment3.h
	$(CC) $(CFLAGS) -I$(INC) -c $(SRC)main.c -o $(BIN)main.o 

$(BIN)P11.o: $(SRC)P11.c 
	$(CC) $(CFLAGS) -I$(INC) -c $(SRC)P11.c -o $(BIN)P11.o 

$(BIN)P12.o: $(SRC)P12.c 
	$(CC) $(CFLAGS) -I$(INC) -c $(SRC)P12.c -o $(BIN)P12.o 

$(BIN)P21.o: $(SRC)P21.c 
	$(CC) $(CFLAGS) -I$(INC) -c $(SRC)P21.c -o $(BIN)P21.o 

$(BIN)P22.o: $(SRC)P22.c 
	$(CC) $(CFLAGS) -I$(INC) -c $(SRC)P22.c -o $(BIN)P22.o 

$(BIN)P23.o: $(SRC)P23.c 
	$(CC) $(CFLAGS) -I$(INC) -c $(SRC)P23.c -o $(BIN)P23.o 

$(BIN)filehandler.o: $(SRC)filehandler.c $(INC)assignment3.h
	$(CC) $(CFLAGS) -I$(INC) -c $(SRC)filehandler.c -o $(BIN)filehandler.o 


clean: 
	rm $(BIN)*.o $(BIN)assignment3