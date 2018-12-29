all: main.o
	gcc -o NAMEHERE  main.o

main.o: main.c
	gcc -c main.c

run: 
	./NAMEHERE

clean:
	rm *.o
	rm ./NAMEHERE
