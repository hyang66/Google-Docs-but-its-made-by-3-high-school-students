all:
	make server_sockets client_sockets

linked_list.o: linked_list.c linked_list.h definitions.h
	gcc -c -g linked_list.c

client_sockets: networking.o linked_list.o client_sockets.o
	gcc -o client_sockets client_sockets.o networking.o linked_list.o -lncurses

server_sockets: networking.o linked_list.o server_sockets.o
	gcc -o server_sockets server_sockets.o networking.o linked_list.o

client_sockets.o: client_sockets.c networking.h linked_list.h definitions.h
	gcc -c client_sockets.c

server_sockets.o: server_sockets.c networking.h linked_list.h definitions.h
	gcc -c server_sockets.c

networking.o: networking.c networking.h
	gcc -c networking.c

pipe_networking.o: pipe_networking.c pipe_networking.h
	gcc -c pipe_networking.c

clean:
	rm *.o
	rm client
	rm server
	rm curses
	rm test
	rm *~
