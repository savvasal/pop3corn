all: server

server: main.o util.o
	gcc main.o util.o -o server

main.o: main.c util.o
	gcc -c main.c

util.o: util.c util.h
	gcc -c util.c

clean:
	-rm -f *.o
	-rm -f *~
	-rm server
