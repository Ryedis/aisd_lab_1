cmake_minimum_required(VERSION 3.11)

project(polynomial CXX)

set(CMAKE_CXX_STANDARD 23)

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS true)

    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
endif()

# Объявляем библиотеку
add_library(polynomial SHARED "include/polynomial/polynomial.h" "src/polynomial.cc")
target_include_directories(polynomial PUBLIC "include")


#Подключение консольного приложения
add_executable(console "console/console.cc")
target_link_libraries(console polynomial)

