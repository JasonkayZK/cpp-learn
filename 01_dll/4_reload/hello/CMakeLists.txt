add_library(hello SHARED src/hello.cc)

add_library(hello_interface INTERFACE include/hello.h)
target_include_directories(hello_interface INTERFACE include)
target_link_libraries(hello_interface INTERFACE reload)
