# Déclare la version minimum de CMake requise
cmake_minimum_required(VERSION 3.10)

# Nom du projet
project(sdl-project CXX)

# Spécifie le standard C++ requis
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Chemins vers SDL2
set(SDL2_DIR C:/Users/trigg/Downloads/SDL2)
set(SDL2_INCLUDE_DIR ${SDL2_DIR}/include)
#set(SDL2_LIB_DIR ${SDL2_DIR}/lib/x64)
set(SDL2_LIB_DIR ${CMAKE_SOURCE_DIR}/libs)

# Spécifie le répertoire contenant les fichiers d'en-tête
include_directories(${CMAKE_SOURCE_DIR}/includes)
message("Shared libs:" ${CMAKE_SOURCE_DIR}/libs )

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/sources/*.cpp)
message("include sources:" ${SOURCES})


# Déclare les fichiers sources pour l'exécutable
add_executable(runable main.cpp ${SOURCES})

# Spécifie le répertoire de recherche pour les bibliothèques
#target_link_directories(runable PRIVATE ${SDL2_LIB_DIR})


# Lie l'exécutable avec la bibliothèque dynamique en utilisant le nom exact
#target_link_libraries(runable PRIVATE -l:SDL2.dll -l:SDL2main.lib -lglew32 -lopengl32)
target_link_libraries(runable PRIVATE -lSDL2 -lSDL2main -lSDL2_image -lglew32 -lopengl32)

add_custom_command(TARGET runable POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/shaders
    $<TARGET_FILE_DIR:runable>/shaders
)

add_custom_command(TARGET runable POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/textures
    $<TARGET_FILE_DIR:runable>/textures
)