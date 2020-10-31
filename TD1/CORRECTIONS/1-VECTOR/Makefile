CC=gcc
CFLAGS=-O3 -Wall
LDFLAGS=-L. -lvector
EXEC=vector
LIB=libvector.so

all: $(LIB) $(EXEC)

$(LIB): vector.c
	gcc $(CFLAGS) -shared -fPIC -o $@ $^

$(EXEC): compute.o main.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

proper:
	rm -rf *.o

clean: $(proper)
	rm -rf *.o $(EXEC) $(LIB)
