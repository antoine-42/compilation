EXE= TP5_1 \
	TP5_2\
	TP5_3\
	TP5_4\
	TP5_5

all: $(EXE)

CXX=g++
CC=gcc

MPICC=mpicc

PLUGIN_FLAGS=-I`$(CC) -print-file-name=plugin`/include -g -Wall -fno-rtti -shared -fPIC

CFLAGS=-g -O3

libplugin_%.so: plugin_%.cpp
	 $(CXX) $(PLUGIN_FLAGS) -o $@ $<

%: libplugin_%.so test2.c
	$(MPICC) test2.c $(CFLAGS) -o $@ -fplugin=./$<

%.pdf: %.dot
	dot -Tpdf $< -o $@

clean:
	rm -rf *.pgr *.pdf TP5_1 TP5_2 TP5_3 TP5_4 TP5_5

clean_all: clean
	rm -rf libplugin.so *.dot
