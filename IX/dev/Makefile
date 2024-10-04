main: main.o tools.o str.o
	gcc -o main main.o tools.o str.o

main.o:
	gcc --std=c99 --pedantic -Wall -c main.c

tools.o:
	gcc --std=c99 --pedantic -Wall -c tools.c

str.o:
	gcc --std=c99 --pedantic -Wall -c str.c

clean:
	rm main main.o tools.o str.o