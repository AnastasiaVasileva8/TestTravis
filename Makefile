.PHONY: clean prepare functions test

bin/udpserver: prepare obj/calc.o obj/calc.o
	gcc -o bin/udpserver obj/calc.o obj/calc.o

obj/cmain.o: prepare obj/main.c
	gcc -Wall -c obj/main.c -o obj/cmain.o -Ithirdparty


obj/calc.o: prepare src/calc.c
	gcc -c src/calc.c -o obj/calc.o

obj/main.o: prepare src/main.c
	gcc -c src/main.c -o obj/main.o

	
clean:
	rm -f bin/* 
	rm -f obj/*
	
functions: bin/udpserver
	bin/udpserver 
	
prepare: bin obj

bin:
	mkdir bin

obj:
	mkdir obj