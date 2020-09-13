CC=gcc
CFLAGS=-Wall -pedantic -ansi 
EXEC=server
OBJ=startserver.o acc_socket.o  storage_server.o

all: $(EXEC)

debug: CFLAGS += -DDBUG=1 -g
debug: all

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

startserver.o: startserver.c acc_socket.h acc.h
	$(CC) $(CFLAGS) -c startserver.c

acc_socket.o: acc_socket.c acc_socket.h acc.h
	$(CC) $(CFLAGS) -c acc_socket.c

storage_server.o: storage_server.c storage_server.h acc.h acc_socket.h
	$(CC) $(CFLAGS) -c storage_server.c

clean:
	rm -rf $(OBJ) $(EXEC)