add_library(GameObjects bullet.cpp spaceship.cpp)

find_package(SDL2 REQUIRED)

target_include_directories(GameObjects
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src
        ${SDL2_INCLUDE_DIRS} 
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(GameObjects 
    PUBLIC
        CustomMath 
        ${SDL2_LIBRARIES}
        )