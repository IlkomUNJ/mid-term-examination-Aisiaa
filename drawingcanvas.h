#ifndef DRAWINGCANVAS_H
#define DRAWINGCANVAS_H

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QPainter>
#include <QMouseEvent>
#include <QPixmap>
#include <iostream>
#include <iomanip>

using namespace std;

class DrawingCanvas : public QWidget {
    Q_OBJECT

private:
    const int MIN_WINDOW_WIDTH = 600;
    const int MIN_WINDOW_HEIGHT = 400;

    QVector<QPoint> m_points;
    QList<QRect> m_candidateRegions;
    bool isPaintLinesClicked = false;

    bool isWindowNonEmpty(const QImage& window, int& nonWhiteCount);
    bool checkSegmentPattern(const QImage& window);

public:
    explicit DrawingCanvas(QWidget *parent = nullptr);

    void clearPoints();
    void paintLines();
    void segmentDetection();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // DRAWINGCANVAS_H

