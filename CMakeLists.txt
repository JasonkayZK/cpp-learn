cmake_minimum_required(VERSION 3.16)
project(cpp_learn)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# Qt config
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
    Core
    Gui
    Widgets
    REQUIRED)
find_package(Qt6Mqtt CONFIG REQUIRED)

add_executable(main
    main.cc
    widget.cc
    widget.ui
)
target_link_libraries(main PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt::Mqtt Qt6::Mqtt Qt::MqttPrivate Qt6::MqttPrivate
)
