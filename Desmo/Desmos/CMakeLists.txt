cmake_minimum_required(VERSION 3.10)
project(Desmos)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Список исходных файлов библиотеки
set(${project}_SOURCES
    Degree/Degree.cpp
    Functions/Functions.cpp
    Indct/Indct.cpp
    Irr/Irr.cpp
    Logo/Logo.cpp
    Trig/Trig.cpp
)

# Список заголовочных файлов библиотеки
set(${project}_HEADERS
    Degree/Degree.h
    Functions/Functions.h
    Indct/Indct.h
    Irr/Irr.h
    Logo/Logo.h
    Trig/Trig.h
)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES}
        ${${project}_HEADERS})

# Создаем статическую библиотеку Desmos
add_library(Desmos STATIC ${${project}_SOURCES} ${${project}_HEADERS})


