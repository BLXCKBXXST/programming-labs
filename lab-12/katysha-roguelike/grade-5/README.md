# Lab 12 katysha-roguelike — Grade 5
gettimeofday() для N=100/10000/100000 + .so
```bash
gcc -Wall -Iinclude -c src/room.c -o room.o
ar rcs libroom.a room.o
gcc -Wall -Iinclude -fPIC -shared src/room.c -o libroom.so
gcc -Wall -Iinclude src/main.c libroom.a -o rooms
./rooms
```
