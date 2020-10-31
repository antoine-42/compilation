CC=gcc
CFLAGS=-O3 -Wall
LDFLAGS=
EXEC=matrix

all: $(EXEC) $(EXEC)_opti

$(EXEC): compute.o matrix.o main.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(EXEC)_opti: compute.o matrix_tiled.o main.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

matrix_tiled.o: matrix.c
	$(CC) $(CFLAGS) -DTILED -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o
