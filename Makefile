default: link

link: dist/main.o dist/function.o
	gcc dist/main.o dist/function.o -o dist/main

dist/main.o: main.c
	gcc -c -Wall main.c -o dist/main.o

dist/function.o: lib/function.c
	gcc -c -Wall lib/function.c -o dist/function.o

clean:
	rm -rf ./dist && mkdir dist
