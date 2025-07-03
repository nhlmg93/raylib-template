CC = gcc
LIB = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

main-reload: main_reload.c plugin.h
	$(CC) -rdynamic -o main-reload main_reload.c -ldl $(LIB)

plugin.so: plugin.c plugin.h
	$(CC) -fPIC -shared -o plugin.so plugin.c

run: main-reload plugin.so
	./main-reload

tests: ./test_*.c
	clear
	@$(CC) unity.c ./test_*.c -o tests.out $(LIB)
	@./tests.out
	@rm tests.out

tests-run:
	@$(CC) main_test.c -o main-test $(LIB)
	@./main-test


clean:
	rm -rf main-reload main-test plugin.so *.o *.out *.out.dSYM
