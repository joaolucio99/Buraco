all:
	@gcc lib/*.h src/*.c main.c -o main `pkg-config --cflags --libs gtk+-3.0` -rdynamic 

run:	
	@./main
	
clean:
	@rm -rf lib/*.gch main
