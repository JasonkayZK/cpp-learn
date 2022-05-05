include_directories(${PROJECT_SOURCE_DIR}/my-tiny-stl)

set(APP_SRC main.cc)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(stltest ${APP_SRC})
