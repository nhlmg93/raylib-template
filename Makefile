CC = gcc
RAYLIB = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

main: main.c
	$(CC) -rdynamic -o main main.c -ldl $(RAYLIB)

plugin.so: plugin.c
	$(CC) -fPIC -shared -o plugin.so plugin.c

run: main plugin.so
	./main

clean:
	rm -f main plugin.so
