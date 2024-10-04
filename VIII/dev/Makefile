main: main.o list.o tools.o
	gcc -o main main.o list.o tools.o

main.o:
	gcc --std=c99 --pedantic -Wall -c main.c

list.o:
	gcc --std=c99 --pedantic -Wall -c list.c

tools.o:
	gcc --std=c99 --pedantic -Wall -c tools.c

clean:
	rm main main.o list.o tools.o