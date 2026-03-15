# создаём библиотеку background из одного файла
add_library(background STATIC background.c)

# нужно добавить текущую папку чтобы background.h нашёлся
# PUBLIC - чтобы main.c тоже видел background.h через #include
target_include_directories(background PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# линкуем с pipes т.к. background.c внутри вызывает read_pipe/write_pipe
# PRIVATE - pipes нужен только здесь, main.c напрямую не пользуется pipes
target_link_libraries(background PRIVATE pipes)
