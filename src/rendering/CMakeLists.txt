add_library(Textures texture.cpp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2_image REQUIRED)
if (SDL2_IMAGE_FOUND)
    message(STATUS "SDL2_IMAGE found: ${SDL2_IMAGE_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "SDL2_IMAGE not found!")
endif()

target_include_directories(Textures
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/include
        ${SDL2_IMAGE_INCLUDE_DIRS} 
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Textures 
    PUBLIC
        GameObjects 
        ${SDL2_IMAGE_LIBRARIES}
        )

add_library(Initialising initialising.cpp)

target_link_libraries(Initialising PUBLIC Textures)