all: main.o
	gcc -o NAMEHERE  main.o

main.o: main.c
	gcc -c main.c

hannasthingyignore.o: hannasthingyignore.c
	gcc -c hannasthingyignore.c

hanna: hannasthingyignore.o
	gcc -o hanna hannasthingyignore.o
	./hanna

run: 
	./NAMEHERE

clean:
	rm *.o
	rm ./NAMEHERE
