# создаём библиотеку background
add_library(background STATIC background.c)
target_include_directories(background PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# PRIVATE: pipes нужен только внутри background, наружу не пробрасывается
target_link_libraries(background PRIVATE pipes)
