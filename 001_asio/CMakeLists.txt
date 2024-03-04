project(001_asio)

add_executable(demo demo.cc)

target_link_libraries(demo PRIVATE Boost::boost)
