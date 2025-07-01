CC = gcc
LIB = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11


main_reload: main_reload.c
	$(CC) -rdynamic -o main_reload main_reload.c -ldl $(LIB)

plugin.so: plugin.c
	$(CC) -fPIC -shared -o plugin.so plugin.c

run: main_reload plugin.so
	./main_reload

tests: ./test_*.c
	clear
	@$(CC) unity.c ./test_*.c -o tests.out $(LIB)
	@./tests.out
	@rm tests.out

tests-run:
	@$(CC) main_test.c -o main-test $(LIB)
	@./main-test


clean:
	rm -rf main_reload plugin.so *.o *.out *.out.dSYM
