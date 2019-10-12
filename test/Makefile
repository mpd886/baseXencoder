CC=gcc
INCLUDE_DIRS=../src
VPATH=../src

tests: tests.o baseX.o
	$(CC) -g -o $@ $^

tests.o: tests.c baseX.h
	$(CC) -g -c $< -o $@ -I$(INCLUDE_DIRS)

baseX.o: baseX.c baseX.h
	$(CC) -g -c $< -o $@ -I$(INCLUDE_DIRS)


.PHONY: clean

clean:
	-rm *.o
	-rm tests
