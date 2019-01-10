all: main.o
	gcc -o go main.o

main.o: main.c
	gcc -c -g main.c

#hannasthingyignore.o: hannasthingyignore.c
	#gcc -c -g hannasthingyignore.c

#hanna: hannasthingyignore.o
	#gcc -o hanna hannasthingyignore.o
	#./hanna

curses: linked_list.o curses.o
	gcc -o curses curses.o -lncurses linked_list.o

curses.o: curses.c linked_list.h definitions.h
	gcc -c curses.c

linked_list.o: linked_list.c linked_list.h definitions.h
	gcc -c -g linked_list.c

test.o: test.c linked_list.h
	gcc -c -g test.c

test: linked_list.o test.o
	gcc -o test test.o linked_list.o

run:
	./NAMEHERE

# kiloexample: kiloexample.c
# 	$(CC) -o kiloexample kiloexample.c -Wall -W -pedantic -std=c99

run2:
	./go

client: client.o pipe_networking.o
	gcc -o client client.o pipe_networking.o

server: server.o pipe_networking.o
	gcc -o server server.o pipe_networking.o

client.o: client.c pipe_networking.h definitions.h
	gcc -c client.c

server.o: server.c pipe_networking.h definitions.h
	gcc -c server.c

pipe_networking.o: pipe_networking.c pipe_networking.h
	gcc -c pipe_networking.c

clean:
	rm *.o
	# rm kiloexample
	rm ./NAMEHERE
