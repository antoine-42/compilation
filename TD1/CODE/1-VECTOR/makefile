CC = gcc
CFLAGS  = -O3 -g -Wall

LDFLAGS = -L. -lvector
OBJS = main.o compute.o
SRCS = main.c compute.c
EXEC = main

all: $(EXEC)

libvector.so: vector.c vector.h
	$(CC) $(CFLAGS) -fPIC -c $< -o $(basename $@).o
	$(CC) $(CFLAGS) -shared $(basename $@).o -o $@

compute.o: compute.c compute.h
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

vector: $(OBJS) libvector.so
	$(CC) $(CFLAGS) OBJS -o $@ $(LDFLAGS)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -shared -fPIC -o libvector.so vector.c && \
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(EXEC) $(SRCS)

clean:
	$(RM) *.so *.o $(EXEC)
