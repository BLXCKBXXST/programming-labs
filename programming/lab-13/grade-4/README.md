# CMake и два вида библиотеки

Здесь один `CMakeLists.txt`, но библиотеку можно собрать статической или динамической. По умолчанию `STATIC`, для `.so` передаётся `-DLIB_TYPE=SHARED`.

```bash
cmake -S . -B build -DLIB_TYPE=STATIC
cmake --build build
./build/sneakers_app
```

Для динамической версии используй `-DLIB_TYPE=SHARED`. При запуске на Linux, если библиотека не находится автоматически, понадобится `LD_LIBRARY_PATH=./build`.

Режим оптимизации меняется через `-DCMAKE_BUILD_TYPE=Debug` или `Release`.
