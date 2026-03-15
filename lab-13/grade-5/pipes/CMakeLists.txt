# создаём библиотеку pipes
# STATIC - значит скомпилируется в .a файл и встраивается прямо в бинарник
# SHARED - был бы .so файл, подгружается в память в рантайм
add_library(pipes STATIC read_pipe.c write_pipe.c)

# PUBLIC - значит что эта папка будет видна не только внутри pipes
# но и любому кто потом подключится к pipes (background например)
# без этого background.c не нашёл бы pipes.h
# ${CMAKE_CURRENT_SOURCE_DIR} - это путь к текущей папке (где лежит этот CMakeLists.txt)
target_include_directories(pipes PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
