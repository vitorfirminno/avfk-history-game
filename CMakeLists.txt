cmake_minimum_required(VERSION 3.16)
project(avfk_history_game C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Encontra todos os arquivos .c do projeto (excluindo diretórios de assets)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.c"
)

list(FILTER SOURCES EXCLUDE REGEX ".*/cmake-assets-.*/.*")
list(FILTER SOURCES EXCLUDE REGEX ".*/cmake-build-.*/.*")
list(FILTER SOURCES EXCLUDE REGEX "${CMAKE_BINARY_DIR}/.*")

add_executable(avfk_history_game ${SOURCES}
        src/entity/player.h
        src/entity/player.c
        src/entity/entity.c
        src/entity/entity.h
        src/core/input.c
        src/core/input.h
        src/graphics/renderer.h
        src/graphics/renderer.c)


find_package(PkgConfig REQUIRED)
pkg_check_modules(ALLEGRO REQUIRED allegro-5 allegro_primitives-5 allegro_image-5)
find_package(SQLite3 REQUIRED)


target_include_directories(avfk_history_game PRIVATE
        src
        include
        ${ALLEGRO_INCLUDE_DIRS}
        ${SQLite3_INCLUDE_DIRS}
)

target_link_libraries(avfk_history_game PRIVATE
        ${ALLEGRO_LIBRARIES}
        ${SQLite3_LIBRARIES}
        m
)

add_custom_command(TARGET avfk_history_game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:avfk_history_game>/assets
)