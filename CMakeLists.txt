cmake_minimum_required(VERSION 3.10)
project(MeshProcessingLibrary)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Подключение HeightMapGenerator
include(FetchContent)
FetchContent_Declare(
    HeightMapGenerator
    GIT_REPOSITORY https://github.com/AlexanderOsharov/HeightMapGenerator.git
    GIT_TAG main
)
FetchContent_MakeAvailable(HeightMapGenerator)

# Создание статической библиотеки
add_library(MeshProcessing STATIC
    src/Mesh.cpp
    src/OBJExporter.cpp
    src/STLExporter.cpp
)

# Подключение заголовочных файлов
target_include_directories(MeshProcessing PUBLIC include)
target_include_directories(MeshProcessing PRIVATE ${HeightMapGenerator_SOURCE_DIR}/include)

# Связывание с HeightMapGenerator
target_link_libraries(MeshProcessing PRIVATE HeightMapGenerator)

# Тестирование
add_executable(MeshProcessingTest tests/main.cpp)
target_link_libraries(MeshProcessingTest PRIVATE MeshProcessing)