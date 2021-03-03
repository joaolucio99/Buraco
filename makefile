all:
	@gcc lib/*.h lib/*/*.h lib/*/*/*.h src/*.c src/*/*.c src/*/*/*.c main.c -o main `pkg-config --cflags --libs gtk+-3.0` -rdynamic 

run:	
	@./main
	
clean:
	@rm -rf lib/*.gch main
