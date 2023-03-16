all: build

.PHONY: clean build install

clean:
	rm -rf *.o btclicker

build:
	gcc -Wall -Wextra -O3 -lncurses -o btclicker *.c

install: build
	cp btclicker /usr/bin

uninstall:
	rm /usr/bin/btclicker
