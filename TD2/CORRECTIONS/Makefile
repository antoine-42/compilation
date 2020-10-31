EXE= TP2_1 \
	TP2_2 \
	TP2_3 \
	TP2_5 \
	TP2_6 \
	TP2_7 \
	TP2_7_bis \
	TP2_8

all: $(EXE)

CXX=g++_910
CC=gcc_910

MPICC=mpicc
MPICXX=mpicxx

PLUGIN_FLAGS=-I`$(CC) -print-file-name=plugin`/include -g -Wall -fno-rtti -shared -fPIC

CFLAGS=-g -O3


libplugin_%.so: plugin_%.cpp
	$(CXX) $(PLUGIN_FLAGS) -o $@ $<

% : libplugin_%.so test.c test2.cpp
	$(MPICC) test.c $(CFLAGS) -o $@ -fplugin=./$< 
	$(MPICXX) test2.cpp $(CFLAGS) -o $@ -fplugin=./$< 

clean:
	rm -rf $(EXE)

clean_all: clean
	rm -rf libplugin*.so *.dot
