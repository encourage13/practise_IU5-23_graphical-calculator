#include <QApplication>
#include "MainWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);  // Создание экземпляра QApplication

    MainWindow mainWindow;         // Создание экземпляра главного окна
    mainWindow.setWindowTitle("Graph Plotter like Desmos");  // Задание заголовка окна
    mainWindow.show();             // Отображение главного окна

    return app.exec();             // Запуск главного цикла обработки событий
}
