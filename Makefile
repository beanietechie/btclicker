include config.mk

PROG_NAME=btclicker
CFLAGS=-Wall -Wextra -Werror
LIBS=-lncurses

RM=rm -f
CP=cp

all: build

.PHONY: clean build install

clean:
	$(RM) $(PROG_NAME)

build:
	$(CC) $(CFLAGS) $(LIBS) -o $(PROG_NAME) $(wildcard *.c)

install: build
	$(CP) $(PROG_NAME) $(INSTALL_DESTINATION)

uninstall:
	$(RM) $(INSTALL_DESTINATION)/$(PROG_NAME)
