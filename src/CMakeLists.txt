
add_subdirectory(game_math)

add_subdirectory(game_objects)

add_subdirectory(rendering)

add_subdirectory(timing)

add_subdirectory(collision)

add_subdirectory(game_text)

add_executable(Asteroids main.cpp)

target_link_libraries(Asteroids PUBLIC Initialising Timing Collider GameTexts)