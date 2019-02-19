gameOfLife: defs.o twoPlayer.o zeroPlayer.o gameIO.o main.o
	gcc defs.o twoPlayer.o zeroPlayer.o gameIO.o main.o -o gameOfLife

defs.o: defs.h defs.c
	gcc -c defs.c

twoPlayer.o: twoPlayer.c defs.o
	gcc -c twoPlayer.c

zeroPlayer.o: zeroPlayer.c defs.o
	gcc -c zeroPlayer.c

gameIO.o: gameIO.c defs.o
	gcc -c gameIO.c

main.o: main.c defs.o
	gcc -c main.c

clean:
	rm -f *.o

