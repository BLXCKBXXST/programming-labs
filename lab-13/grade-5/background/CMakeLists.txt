# Создаём библиотеку background из background.c
add_library(background STATIC background.c)

# Добавляем текущую папку в include-пути (background.h лежит здесь же)
target_include_directories(background PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Линкуем background с библиотекой pipes
# PRIVATE: pipes нужен только внутри background, наружу не пробрасывается
target_link_libraries(background PRIVATE pipes)
