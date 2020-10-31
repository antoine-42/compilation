EXE= TP4_5\
		 TP4_6\
		 TP4_7\
		 TP4_8

all: $(EXE)

CXX=g++_910
CC=gcc_910

CXX=g++
CC=gcc

MPICC=mpicc

PLUGIN_FLAGS=-I`$(CC) -print-file-name=plugin`/include -g -Wall -fno-rtti -shared -fPIC

CFLAGS=-g -O3

libplugin_%.so: plugin_%.cpp
	 $(CXX) $(PLUGIN_FLAGS) -o $@ $<

%: libplugin_%.so test3.c
	$(MPICC) test3.c $(CFLAGS) -o $@ -fplugin=./$<

%.pdf: %.dot
	dot -Tpdf $< -o $@

clean:
	rm -rf *.pgr *.pdf

clean_all: clean
	rm -rf libplugin.so *.dot TP4_*
