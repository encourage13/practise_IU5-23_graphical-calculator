#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QWheelEvent>

class GraphWidget : public QGraphicsView {
    Q_OBJECT

public:
    GraphWidget(QWidget* parent = nullptr);
    void drawGraph(const std::vector<QPointF>& points);

protected:
    QGraphicsScene* scene;
    QPixmap buffer;
    QGraphicsPixmapItem* bufferItem;
    QPoint lastMousePos;
    bool dragging;
    qreal zoomFactor = 1.0;  

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void drawAxes(QPainter* painter);
    void drawGrid(QPainter* painter);
    void prepareBuffer();
    void updateScene();
};

#endif // GRAPHWIDGET_H
