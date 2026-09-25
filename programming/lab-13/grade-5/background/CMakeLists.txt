# создаём библиотеку background из background.c
add_library(background STATIC background.c)
# добавляем текущую папку в include-пути
target_include_directories(background PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# PRIVATE: pipes нужен только внутри background
target_link_libraries(background PRIVATE pipes)
