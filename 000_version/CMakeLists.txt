project(000_version)

add_executable(000_version_bin main.cpp)

target_link_libraries(000_version_bin PRIVATE Boost::boost)
