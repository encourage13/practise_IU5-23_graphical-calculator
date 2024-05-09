#include "GraphWidget.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QPen>
#include <QScrollBar>

GraphWidget::GraphWidget(QWidget* parent) : QGraphicsView(parent) {
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    scene = new QGraphicsScene(this);
    setScene(scene);
    buffer = QPixmap(1400, 1000); // Предполагаем начальный размер буфера
    buffer.fill(Qt::white);
    bufferItem = new QGraphicsPixmapItem();
    scene->addItem(bufferItem);
    prepareBuffer();
    setDragMode(QGraphicsView::NoDrag);

    qreal initialScale = 4;  // масштаб 
    setTransform(QTransform::fromScale(initialScale, initialScale));
}

void GraphWidget::drawGraph(const std::vector<QPointF>& points) {
    QPainter painter(&buffer);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::blue, 1.5); 
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);
    qreal centerX = buffer.width() / 2;
    qreal centerY = buffer.height() / 2;
    int unit = 10;  // Размер одной клетки в пикселях, каждая клетка соответствует 1 на графике
    qreal offset = 0.5;
    if (points.size() > 1) {
        for (size_t i = 0; i < points.size() - 1; ++i) {
            QPointF startPoint(centerX + points[i].x() * unit + offset, centerY - points[i].y() * unit + offset);
            QPointF endPoint(centerX + points[i + 1].x() * unit + offset, centerY - points[i + 1].y() * unit + offset);
            painter.drawLine(startPoint, endPoint);
        }
    }

    if (bufferItem) {
        bufferItem->setPixmap(QPixmap::fromImage(buffer.toImage()));
    }
    else {
        bufferItem = new QGraphicsPixmapItem(QPixmap::fromImage(buffer.toImage()));
        scene->addItem(bufferItem);
    }
}



void GraphWidget::prepareBuffer() {
    QPainter painter(&buffer);
    buffer.fill(Qt::white); 

    drawGrid(&painter); 
    drawAxes(&painter); 

    if (bufferItem) {
        bufferItem->setPixmap(QPixmap::fromImage(buffer.toImage()));
    }
    else {
        bufferItem = new QGraphicsPixmapItem(QPixmap::fromImage(buffer.toImage()));
        scene->addItem(bufferItem);
    }
}

void GraphWidget::drawAxes(QPainter* painter) {
    QPen pen(Qt::black, 1);
    painter->setPen(pen);
    int centerX = buffer.width() / 2;
    int centerY = buffer.height() / 2;

    painter->drawLine(centerX, 0, centerX, buffer.height()); 
    painter->drawLine(0, centerY, buffer.width(), centerY);  
}


void GraphWidget::drawGrid(QPainter* painter) {
    QPen pen(Qt::lightGray, 1);
    painter->setPen(pen);
    int centerX = buffer.width() / 2;
    int centerY = buffer.height() / 2;
    int step = 10;  // Размер клетки в пикселях, каждая клетка соответствует 1 на графике


    for (int x = centerX % step; x < buffer.width(); x += step) {
        painter->drawLine(x, 0, x, buffer.height());
    }

 
    for (int y = centerY % step; y < buffer.height(); y += step) {
        painter->drawLine(0, y, buffer.width(), y);
    }
}



void GraphWidget::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::RightButton) {
        lastMousePos = event->pos();
        dragging = true;
        setCursor(Qt::ClosedHandCursor);
    }
}

void GraphWidget::mouseMoveEvent(QMouseEvent* event) {
    if (dragging) {
        QPoint delta = event->pos() - lastMousePos;
        lastMousePos = event->pos();
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
        verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
    }
}

void GraphWidget::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::RightButton) {
        dragging = false;
        setCursor(Qt::ArrowCursor);
    }
}

void GraphWidget::wheelEvent(QWheelEvent* event) {
    qreal scaleFactor = 1.1;  // Фактор масштабирования
    // Определяем, увеличивать или уменьшать масштаб
    if (event->angleDelta().y() > 0) {
        scale(scaleFactor, scaleFactor);
    }
    else {
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}

void GraphWidget::updateScene() {
    scene->update();  
}
