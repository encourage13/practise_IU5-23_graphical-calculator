#include <QApplication>
#include "MainWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);  // Ñîçäàíèå ýêçåìïëÿðà QApplication

    MainWindow mainWindow;         // Ñîçäàíèå ýêçåìïëÿðà ãëàâíîãî îêíà
    mainWindow.setWindowTitle("Desmo");  // Çàäàíèå çàãîëîâêà îêíà
    mainWindow.show();             // Îòîáðàæåíèå ãëàâíîãî îêíà

    return app.exec();             // Çàïóñê ãëàâíîãî öèêëà îáðàáîòêè ñîáûòèé
}
