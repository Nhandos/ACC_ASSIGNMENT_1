CC=gcc
CFLAGS=-Wall -pedantic -ansi 
EXEC=server
OBJ=startserver.o acc_socket.o 

all: $(EXEC)

debug: CFLAGS += -DDBUG=1 -g
debug: all

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

startserver.o: startserver.c acc_socket.h acc.h
	$(CC) $(CFLAGS) -c startserver.c

acc_socket.o: acc_socket.c acc_socket.h acc.h
	$(CC) $(CFLAGS) -c acc_socket.c

clean:
	rm -rf $(OBJ) $(EXEC)