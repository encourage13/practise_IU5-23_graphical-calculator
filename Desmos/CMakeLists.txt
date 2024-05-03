cmake_minimum_required (VERSION 3.8)
set(PROJECT_NAME Desmos)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 20)
set(SOURCES
        Functions/Functions.cpp
        Logo/Logo.cpp
        Indct/Indct.cpp
        Desmos/main.cpp
        Irr/Irr.cpp
        Trig/Trig.cpp
        Degree/Degree.cpp
)
set(HEADERS
        Functions/Functions.h
        Logo/Logo.h
        Indct/Indct.h
        Irr/Irr.h
        Trig/Trig.h
        Degree/Degree.h
)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC Functions Logo  Indct Irr Trig Degree)
