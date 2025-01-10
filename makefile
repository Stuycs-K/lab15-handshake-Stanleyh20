all: client server
compile: basic_client.o basic_server.o persistant_server.o forking_server.o pipe_networking.o
	@gcc -o client1 basic_client.o pipe_networking.o
	@gcc -o server basic_server.o pipe_networking.o
	@gcc -o persistant persistant_server.o pipe_networking.o
	@gcc -o forking forking_server.o pipe_networking.o

basic_client.o: basic_client.c pipe_networking.h
	@gcc -c basic_client.c

basic_server.o: basic_server.c pipe_networking.h
	@gcc -c basic_server.c

persistant_server.o: persistant_server.c pipe_networking.h
	@gcc -c persistant_server.c

forking_server.o: forking_server.c pipe_networking.h
	@gcc -c forking_server.c

pipe_networking.o: pipe_networking.c pipe_networking.h
	@gcc -c pipe_networking.c

server: forking
	@./forking

client: client1
	@./client1
clean:
	@rm -rf *.o
	@rm -rf client1 server persistant forking
