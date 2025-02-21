add_library(Collider collision.cpp)

find_package(SDL2 REQUIRED)

target_include_directories(Collider 
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src
        ${SDL2_INCLUDE_DIRS} 
    INTERFACE 
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Collider
    PUBLIC
        ${SDL2_LIBRARIES}
        )
