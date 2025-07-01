CC = gcc
RAYLIB = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

LIBS = -lm

main: main.c
	$(CC) -rdynamic -o main main.c -ldl $(RAYLIB)

plugin.so: plugin.c
	$(CC) -fPIC -shared -o plugin.so plugin.c

run: main plugin.so
	./main

tests: ./test_*.c
	@echo Compiling $@
	@$(CC) unity.c ./test_*.c -o tests.out $(LIBS)
	@./tests.out

clean:
	rm -rf main plugin.so *.o *.out *.out.dSYM
