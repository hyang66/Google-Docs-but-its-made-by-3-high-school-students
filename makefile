all: main.o
	gcc -o go main.o

main.o: main.c
	gcc -c main.c

hannasthingyignore.o: hannasthingyignore.c
	gcc -c hannasthingyignore.c

hanna: hannasthingyignore.o
	gcc -o hanna hannasthingyignore.o
	./hanna


kiloexample: kiloexample.c
	$(CC) -o kiloexample kiloexample.c -Wall -W -pedantic -std=c99

run:
	./go

clean:
	rm *.o
	rm kiloexample
	rm ./NAMEHERE
