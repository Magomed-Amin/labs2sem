trees: main.o computer.o tools.o
	gcc -o main main.o computer.o tools.o

main.o:
	gcc --std=c99 --pedantic -Wall -c main.c

computer.o:
	gcc --std=c99 --pedantic -Wall -c computer.c

tools.o:
	gcc --std=c99 --pedantic -Wall -c tools.c

clean:
	rm main main.o computer.o tools.o
