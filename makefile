CC=gcc
CFLAGS=-Wall -ansi 
EXECS=acc_server acc_client
OBJ_SERV=startserver.o acc_socket.o  storage_server.o
OBJ_CLI=startclient.o acc_socket.o storage_client.o

all: $(EXECS)

debug: CFLAGS += -DDEBUG=1 -g
debug: all

acc_server: $(OBJ_SERV)
	$(CC) $(CFLAGS) $(OBJ_SERV) -o acc_server

acc_client: $(OBJ_CLI)
	$(CC) $(CFLAGS) $(OBJ_CLI) -o acc_client

startserver.o: startserver.c acc_socket.h acc.h
	$(CC) $(CFLAGS) -c startserver.c

startclient.o: startclient.c acc_socket.h acc.h
	$(CC) $(CFLAGS) -c startclient.c

acc_socket.o: acc_socket.c acc_socket.h acc.h
	$(CC) $(CFLAGS) -c acc_socket.c

storage_client.o: storage_client.c storage_client.h acc.h acc_socket.h
	$(CC) $(CFLAGS) -c storage_client.c

storage_server.o: storage_server.c storage_server.h acc.h acc_socket.h
	$(CC) $(CFLAGS) -c storage_server.c

clean:
	rm -rf $(OBJ_CLI) $(OBJ_SERV) $(EXECS)