add_library(CustomMath math.cpp)

target_include_directories(CustomMath INTERFACE 
                            ${CMAKE_CURRENT_SOURCE_DIR}
                           )

