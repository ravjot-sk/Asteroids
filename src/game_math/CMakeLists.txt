add_library(CustomMath custom_math.cpp)

target_include_directories(CustomMath INTERFACE 
                            ${CMAKE_CURRENT_SOURCE_DIR}
                           )

