all: app

app: crypt_xtea.o main.o
	gcc -Wall -o app crypt_xtea.o main.o

crypt_xtea.o: src/crypt_xtea.c
	gcc -c -Wall src/crypt_xtea.c

main.o: main.c
	gcc -c -Wall -Wno-unused-function main.c

clean:
	rm -f *.o
	rm -f app