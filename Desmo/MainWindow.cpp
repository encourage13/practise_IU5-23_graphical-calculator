#include "MainWindow.h"
#include <QVBoxLayout>
#include <vector>
#include <QPointF>
#include <QScreen>
#include "Desmos/Functions/Functions.h"


std::vector<QPointF> calculat(const std::string& expression) {
    std::vector<QPointF> points;
                   
    std::vector<Cord> cords = Get(expression);

    for (const auto& cord : cords) {
        points.emplace_back(cord.x, cord.y);
    }

    return points;
}

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenSize = screen->availableGeometry();
    resize(screenSize.width() * 0.8, screenSize.height() * 0.8); // Задаем размер окна как 80% от доступного размера экрана

    auto* widget = new QWidget();
    setCentralWidget(widget);

    auto* layout = new QVBoxLayout(widget);
    lineEdit = new QLineEdit();
    button = new QPushButton("Draw a graph");
    graphWidget = new GraphWidget();

    layout->addWidget(lineEdit);
    layout->addWidget(button);
    layout->addWidget(graphWidget);
        
    connect(button, &QPushButton::clicked, this, &MainWindow::calculateAndDraw);
}

void MainWindow::calculateAndDraw() {
    QString input = lineEdit->text();
    if (input.isEmpty()) {
        qDebug() << "Input is empty!";
        return;
    }

    std::vector<QPointF> points = calculat(input.toStdString());

    graphWidget->drawGraph(points);
}
