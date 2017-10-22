CC =gcc -Werror 

all: play

build: clear compile
	
compile:
	$(CC) -c main.c
	
	$(CC) -o main main.o -lm
run:
	./main

clear:
	rm -f main
	rm -f out.wav
	rm -f main.o

play: build
	./main | ffplay -nodisp -ar 44100 -ac 1 -f s16le -i pipe:0

store: build
	rm -f out.wav
	./main | ffmpeg -ar 44100 -ac 1 -f s16le -i pipe:0 out.wav
