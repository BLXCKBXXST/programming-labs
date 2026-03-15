# Lab 12 katysha-roguelike — Grade ★
Callback для сортировки + замер времени.
```bash
gcc -Wall -Iinclude -c src/room.c -o room.o
ar rcs libroom.a room.o
gcc -Wall -Iinclude src/main.c libroom.a -o rooms
./rooms
```
