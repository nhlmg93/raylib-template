CC = gcc
LIB = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

dev:
	$(CC) -rdynamic -o build/main-dev main_dev.c $(LIB)

plugin.so:
	$(CC) -fPIC -shared -o build/plugin.so plugin.c

run: dev plugin.so
	./build/main-dev

clean:
	rm -rf build
