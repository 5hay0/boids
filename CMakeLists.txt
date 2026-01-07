cmake_minimum_required(VERSION 3.15)
project(boids)

set(CMAKE_CXX_STANDARD 17)


# --- EXÉCUTABLE PRINCIPAL ---
add_executable(boids
    src/main.cpp
    src/Boid.cpp
    src/Rule.cpp
    src/Flock.cpp
    src/Settings.cpp
    src/Simulation.cpp
    src/SaveSystem.cpp
)


set(SFML_DIR "api/SFML-3.0.2/lib/cmake/SFML")


find_package(SFML 3.0.2 CONFIG REQUIRED COMPONENTS
        System
        Window
        Graphics
        Audio
)


target_link_libraries(boids PRIVATE
        SFML::System
        SFML::Window
        SFML::Graphics
        SFML::Audio
)

add_custom_command(TARGET boids POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:boids>
        $<TARGET_FILE_DIR:boids>
        COMMAND_EXPAND_LISTS
)

set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP TRUE)

file(COPY ${CMAKE_SOURCE_DIR}/asset
     DESTINATION ${CMAKE_BINARY_DIR})