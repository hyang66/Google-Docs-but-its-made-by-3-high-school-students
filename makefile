all: main.o
	gcc -o NAMEHERE  main.o

main.o: main.c
	gcc -c -g main.c

hannasthingyignore.o: hannasthingyignore.c
	gcc -c -g hannasthingyignore.c

hanna: hannasthingyignore.o
	gcc -o hanna hannasthingyignore.o
	./hanna

linked_list.o: linked_list.c linked_list.h
	gcc -c -g linked_list.c

test.o: test.c linked_list.h
	gcc -c -g test.c

test: linked_list.o test.o
	gcc -o test test.o linked_list.o

run: 
	./NAMEHERE

clean:
	rm *.o
	rm ./NAMEHERE
