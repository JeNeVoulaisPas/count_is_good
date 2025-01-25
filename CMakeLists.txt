cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(count_is_good VERSION 1.0 LANGUAGES CXX)

# Spécifie la version de C++ à utiliser
set(CMAKE_CXX_STANDARD 17)

# Ajout de la bibliothèque (MT et TileSet)
add_library(MyLibrary
        src/MT.cpp
        src/TileSet.cpp
        src/Solver.cpp
        src/main.cpp
)

# Inclure les fichiers d'en-tête pour la bibliothèque
target_include_directories(MyLibrary PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Ajout de l'exécutable principal
add_executable(count_is_good
        src/main.cpp

)

# Lier la bibliothèque à l'exécutable principal
target_link_libraries(count_is_good PRIVATE MyLibrary)
