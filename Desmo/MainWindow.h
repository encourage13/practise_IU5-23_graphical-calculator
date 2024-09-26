#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include "GraphWidget.h"
#include "Desmos/Functions/Functions.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

private:
    QLineEdit* lineEdit;
    QPushButton* button;
    GraphWidget* graphWidget;
    void calculateAndDraw();
};

#endif // MAINWINDOW_H
