EXE = flashing
CC = gcc
LDFLAGS = -lGL -lglfw
CFLAGS = -DPROGNAME=\"$(EXE)\"

SRC = main.c
OBJ = $(SRC:.c=.o)

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(EXE)
	rm -f $(OBJ)
