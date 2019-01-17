forking: client fserver

select: sclient sserver

sserver: select_server.o networking.o
	gcc -o server select_server.o networking.o

fserver: forking_server.o networking.o
	gcc -o server forking_server.o networking.o

sclient: select_client.o networking.o
	gcc -o client select_client.o networking.o

client: client.o networking.o
	gcc -o client client.o networking.o

#client1: client1.o networking.o linked_list.o
	#gcc -o client1 client1.o networking.o linked_list.o -lncurses

#server1: server1.o networking.o linked_list.o
	#gcc -o server1 server1.o networking.o linked_list.o

#client1.o: client1.c networking.h linked_list.h definitions.h
	#gcc -c client1.c networking.c

#server1.o: server1.c networking.h linked_list.h definitions.h
	#gcc -c server1.c networking.c

#linked_list.o: linked_list.c linked_list.h
	#gcc -c linked_list.c

select_client.o: select_client.c networking.h
	gcc -c select_client.c

client.o: client.c networking.h
	gcc -c client.c

select_server.o: select_server.c networking.h
	gcc -c select_server.c

forking_server.o: forking_server.c networking.h
	gcc -c forking_server.c

networking.o: networking.c networking.h
	gcc -c networking.c

clean:
	rm *.o
	rm *~
