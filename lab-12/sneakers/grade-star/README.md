# Lab 12 sneakers — Grade ★
Callback + замер времени.
```bash
gcc -Wall -Iinclude -c src/sneakers.c -o sneakers.o
ar rcs libsneakers.a sneakers.o
gcc -Wall -Iinclude src/main.c libsneakers.a -o sneakers
./sneakers
```
