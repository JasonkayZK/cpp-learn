project(02_lua)

add_executable(02_lua_main main.cc)
add_library(testlib SHARED testlib.cc)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

find_package(Lua REQUIRED)
target_include_directories(02_lua_main PRIVATE ${LUA_INCLUDE_DIR})

target_link_libraries(testlib PRIVATE ${LUA_LIBRARIES})
target_link_libraries(02_lua_main PRIVATE testlib ${LUA_LIBRARIES})
