cmake_minimum_required(VERSION 3.25)
project(lab1)

set(CMAKE_CXX_STANDARD 17)
add_executable(lab1 main.cpp)

#SFML
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/Users/principalis/all/being/projects/cpp/tas/lab1/SFML/lib/cmake/SFML")
find_package(SFML COMPONENTS graphics window system REQUIRED)

include_directories("C:/Users/principalis/all/being/projects/cpp/tas/lab1/SFML/include/SFML")


target_link_libraries(lab1 sfml-graphics sfml-window sfml-system)