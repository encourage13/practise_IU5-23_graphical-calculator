cmake_minimum_required(VERSION 3.16)
project(Des/Mos VERSION 1.0.0 LANGUAGES CXX)


# Устанавливаем стандарт C++ и включаем MOC/UIC/RCC
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Путь к установке Qt
list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.7.0/msvc2019_64")

# Находим необходимые компоненты Qt
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

# Добавляем директорию библиотеки Desmos как подпроект
add_subdirectory(Desmos)

# Исходные файлы основного проекта
set(SOURCES
    main.cpp
    MainWindow.cpp
    GraphWidget.cpp
)

# Заголовочные файлы основного проекта
set(HEADERS
    MainWindow.h
    GraphWidget.h
)

# UI файлы
set(FORMS
    Desmo.ui
)

# Ресурсные файлы
set(RESOURCES
    Desmo.qrc
)

# Создаем исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${FORMS} ${RESOURCES})


# Связываем с библиотеками Qt
target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Gui Qt6::Widgets)

# Связываем с библиотекой Desmos
target_link_libraries(${PROJECT_NAME} Desmos)
