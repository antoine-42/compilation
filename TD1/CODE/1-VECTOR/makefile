CC = gcc
CFLAGS  = -O3 -g -Wall

LFLAGS = -L/home/antoine/git/projects/ensiie/s5/compilation/TD1/CODE/1-VECTOR
LIBS = -lvector
SRCS = main.c compute.c
MAIN = main

all:    $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) -shared -fPIC -o libvector.so vector.c && \
	$(CC) $(CFLAGS) $(LFLAGS) $(LIBS) -o $(MAIN) $(SRCS)

clean:
	$(RM) *.so *.o $(MAIN)
