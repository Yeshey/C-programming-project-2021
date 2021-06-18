all:
	gcc src/*.c -o dist/main && ./dist/main
    	#gcc src/main.c src/utils.c -o main -lm && ./main
clean:
	rm -f main.o
