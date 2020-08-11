PROJECT(pong)
cmake_minimum_required(VERSION 2.8.11)

add_subdirectory(libs/SFML)

include_directories(include /usr/local/include)
link_directories(/usr/local/lib)

file(GLOB source
	"src/*.cpp"
)

add_executable(pong
	${source}
)

target_link_libraries(pong sfml-graphics sfml-window sfml-system)

add_custom_command(TARGET pong PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:pong>)
