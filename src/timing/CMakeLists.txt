add_library(Timing timer.cpp)

find_package(SDL2 REQUIRED)
target_include_directories(Timing 
    PUBLIC 
        ${SDL2_INCLUDE_DIRS}
    INTERFACE 
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(Timing
    PUBLIC
        ${SDL2_LIBRARIES}
    )
