cmake_minimum_required(VERSION 3.15)
project(MeshProcessingLibrary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем HeightMapGenerator как зависимость
find_package(Git REQUIRED)
if(NOT EXISTS "${CMAKE_BINARY_DIR}/HeightMapGenerator")
    message(STATUS "Cloning HeightMapGenerator...")
    execute_process(
        COMMAND ${GIT_EXECUTABLE} clone https://github.com/AlexanderOsharov/HeightMapGenerator.git ${CMAKE_BINARY_DIR}/HeightMapGenerator
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        RESULT_VARIABLE GIT_CLONE_RESULT
    )
    if(NOT GIT_CLONE_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone HeightMapGenerator")
    endif()
endif()

add_subdirectory(${CMAKE_BINARY_DIR}/HeightMapGenerator ${CMAKE_BINARY_DIR}/HeightMapGenerator-build)

# Добавляем свои исходные файлы
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

add_library(MeshProcessingLibrary STATIC ${SOURCES} ${HEADERS})

# Подключение заголовочных файлов
target_include_directories(MeshProcessingLibrary PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/HeightMapGenerator/include>
    $<INSTALL_INTERFACE:include/HeightMapGenerator>
)

# Связывание с HeightMapGenerator
target_link_libraries(MeshProcessingLibrary PRIVATE HeightMapGenerator)

# Установка библиотеки
install(TARGETS MeshProcessingLibrary
    EXPORT MeshProcessingLibraryTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)
install(EXPORT MeshProcessingLibraryTargets DESTINATION cmake)