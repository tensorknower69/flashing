EXE = flashing
CC = gcc
LDFLAGS = -lGL -lglfw
CFLAGS = -DPROGNAME=\"$(EXE)\"
PREFIX = /usr/local

SRC = main.c
OBJ = $(SRC:.c=.o)

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

install: all
	mkdir -p $(PREFIX)/bin
	install -m 775 $(EXE) $(PREFIX)/bin/$(EXE)

uninstall:
	rm -f $(PREFIX)/bin/$(EXE)

clean:
	rm -f $(EXE)
	rm -f $(OBJ)
