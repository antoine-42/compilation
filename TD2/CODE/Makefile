EXE= TP2_1 \
	TP2_2 \
	TP2_3 \
	TP2_5 \
	TP2_6 \
	TP2_7 \
	TP2_7_bis \
	TP2_8 

all: $(EXE)

CXX=g++
CC=gcc-9
GCC=gcc-9

MPICC=mpicc

PLUGIN_FLAGS=-I`$(CC) -print-file-name=plugin`/include -g -Wall -fno-rtti -shared -fPIC

CFLAGS=-g -O3 -Wall -I/usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/plugin/include -fno-rtti
OBJS=plugin.o
EXEC=plugin.so

plugin.o: plugin.cpp
	$(GCC) $(CFLAGS) -fPIC -c $< -o $@

plugin.so: $(OBJS)
	$(GCC) $(CFLAGS) $(OBJS) -shared -c $< -o $@


libplugin_%.so: plugin_%.cpp
	$(CXX) $(PLUGIN_FLAGS) $(GMP_CFLAGS) -o $@ $<

% : libplugin_%.so test.c
	$(MPICC) test.c $(CFLAGS) -o $@ -fplugin=./$< 

clean:
	rm -rf $(EXE) *.o *.so

clean_all: clean
	rm -rf libplugin*.so *.dot
