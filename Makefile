CC ?= gcc
LDFLAGS = -lGL -lglfw
VERSION = 0.2.0.2
CFLAGS = -Wall -DVERSION=\"$(VERSION)\"
PREFIX ?= /usr/local

SRC = main.c
OBJ = $(SRC:.c=.o)

.PHONY: install uninstall clean

all: flashing

flashing: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

install: all
	mkdir -p $(PREFIX)/bin
	install -m 775 flashing $(PREFIX)/bin/flashing
	mkdir -p $(PREFIX)/share/man/man1
	install -m 664 flashing.1 $(PREFIX)/share/man/man1/flashing.1

uninstall:
	rm -f $(PREFIX)/bin/flashing
	rm -f $(PREFIX)/share/man/man1/flashing.1

clean:
	rm -f flashing $(OBJ)
