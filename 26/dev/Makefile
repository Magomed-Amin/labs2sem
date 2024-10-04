main: main.o tools.o
	gcc -o main main.o tools.o

main.o:
	gcc --std=c99 --pedantic -Wall -c main.c

tools.o:
	gcc --std=c99 --pedantic -Wall -c tools.c

clean:
	rm main main.o tools.o