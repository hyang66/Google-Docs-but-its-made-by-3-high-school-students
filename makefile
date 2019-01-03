all: main.o
	gcc -o go main.o

main.o: main.c
	gcc -c -g main.c

hannasthingyignore.o: hannasthingyignore.c
	gcc -c -g hannasthingyignore.c

hanna: hannasthingyignore.o
	gcc -o hanna hannasthingyignore.o
	./hanna

curses:
	gcc -o curses curses.c -lncurses

#<<<<<<< HEAD
linked_list.o: linked_list.c linked_list.h
	gcc -c -g linked_list.c

test.o: test.c linked_list.h
	gcc -c -g test.c

test: linked_list.o test.o
	gcc -o test test.o linked_list.o

run: 
	./NAMEHERE
#=======

kiloexample: kiloexample.c
	$(CC) -o kiloexample kiloexample.c -Wall -W -pedantic -std=c99

run2:
	./go
#>>>>>>> 5da8c2f117a74127eb0f136cb463aae4bb20f78e

clean:
	rm *.o
	rm kiloexample
	rm ./NAMEHERE
