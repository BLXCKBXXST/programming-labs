# Lab 12 sneakers — Grade 5
gettimeofday() для N=100/10000/100000 + динамическая библиотека.
```bash
gcc -Wall -Iinclude -c src/sneakers.c -o sneakers.o
ar rcs libsneakers.a sneakers.o
gcc -Wall -Iinclude -fPIC -shared src/sneakers.c -o libsneakers.so
gcc -Wall -Iinclude src/main.c libsneakers.a -o sneakers
./sneakers
```
