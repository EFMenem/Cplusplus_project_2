cmake_minimum_required(VERSION 3.22)
project(ayp2_plantilla_tp_grupal_2c2023)

set(CMAKE_C_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../")
set(CXXFLAGS "-Wall -Werror -Wconversion -std=c++20")
set(CMAKE_CXX_FLAGS "${CXXFLAGS}")

include_directories(include)
include_directories(src)
# include_directories(bGVjdG9y)

add_executable(ayp2_plantilla_tp_grupal_2c2023
        src/Placa.cpp
        # bGVjdG9y/bGVjdG9y.cpp
        # bGVjdG9y/ZGVjb2Rl.cpp
        main.cpp
        src/Arma.cpp
        src/Laberinto.cpp
        src/Grafo.cpp
        src/Matriz.cpp
        src/Dijkstra.cpp
        src/Floyd.cpp
        src/InventarioArmas.cpp
        src/Juego.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "main")