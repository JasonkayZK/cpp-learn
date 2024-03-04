project(000_version)

add_executable(version version.cpp)

target_link_libraries(version PRIVATE Boost::boost)
