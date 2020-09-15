1:
```bash
$ gcc -o out.o main.c compute.c vector.c
ELAPSED TIME: 2.5 s
```

3:
ELAPSED TIME: 2.5 s

4:
ELAPSED TIME: 0.24 s

5: 
```
gcc -Wall -O3 -shared -fPIC -o libvector.so vector.c 
gcc -Wall -O3 -L/home/antoine/git/projects/ensiie/s5/compilation/TD1/CODE/1-VECTOR -lvector -o out.o main.c compute.c
```