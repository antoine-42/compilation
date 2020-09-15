all:
	gcc -Wall -O3 -shared -fPIC -o libvector.so vector.c && gcc -Wall -O3 -L/home/antoine/git/projects/ensiie/s5/compilation/TD1/CODE/1-VECTOR -lvector -o out.o main.c compute.c

clean:
	rm *.so *.o