cmake_minimum_required(VERSION 3.11)

project(Sudoku LANGUAGES C)


find_package(Allegro CONFIG REQUIRED)

file(GLOB SOURCE_FILES "src/*.c")

add_executable(Sudoku ${SOURCE_FILES})

target_include_directories(Sudoku PRIVATE include)

target_link_libraries(Sudoku PRIVATE
    Allegro::allegro
    Allegro::allegro_main
    Allegro::allegro_font
    Allegro::allegro_ttf
    Allegro::allegro_primitives
    Allegro::allegro_image
)

if(MSVC)
    target_compile_options(Sudoku PRIVATE /W4)
else()
    target_compile_options(Sudoku PRIVATE -Wall -Wextra)
endif()

add_custom_command(TARGET Sudoku POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/fonts
        $<TARGET_FILE_DIR:Sudoku>/fonts
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/puzzles
        $<TARGET_FILE_DIR:Sudoku>/puzzles
)