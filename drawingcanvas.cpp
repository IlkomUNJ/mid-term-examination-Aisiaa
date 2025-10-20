#include "drawingcanvas.h"
#include <QDebug>
#include <QColor>
#include <iostream>

using namespace std;

DrawingCanvas::DrawingCanvas(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(this->MIN_WINDOW_WIDTH, this->MIN_WINDOW_HEIGHT);
    setStyleSheet("background-color: white; border: 1px solid gray;");
}

void DrawingCanvas::clearPoints() {
    m_points.clear();
    m_candidateRegions.clear();
    update();
}

void DrawingCanvas::paintLines() {
    cout << "[INFO] Paint lines dipanggil" << endl;
    isPaintLinesClicked = true;
    update();
}

bool DrawingCanvas::isWindowNonEmpty(const QImage& window, int& nonWhiteCount) {
    nonWhiteCount = 0;
    const int NON_EMPTY_THRESHOLD = 5;

    for (int y = 0; y < window.height(); ++y) {
        for (int x = 0; x < window.width(); ++x) {
            if (window.pixel(x, y) != 0xffffffff) {
                nonWhiteCount++;
                if (nonWhiteCount > NON_EMPTY_THRESHOLD)
                    return true;
            }
        }
    }
    return nonWhiteCount > NON_EMPTY_THRESHOLD;
}

bool DrawingCanvas::checkSegmentPattern(const QImage& window) {
    int nonWhiteCount = 0;
    isWindowNonEmpty(window, nonWhiteCount);

    const int TOTAL_DENSITY_THRESHOLD = 5;
    if (nonWhiteCount <= TOTAL_DENSITY_THRESHOLD)
        return false;

    int center_pixels = 0;
    int w = window.width();
    int h = window.height();

    int start_x = w / 4;
    int end_x = 3 * w / 4;
    int start_y = h / 4;
    int end_y = 3 * h / 4;

    for (int y = start_y; y < end_y; ++y) {
        for (int x = start_x; x < end_x; ++x) {
            if (window.pixel(x, y) != 0xffffffff)
                center_pixels++;
        }
    }

    const int CENTER_DENSITY_THRESHOLD = 3;
    return (center_pixels >= CENTER_DENSITY_THRESHOLD);
}

void DrawingCanvas::segmentDetection() {
    m_candidateRegions.clear();

    QPixmap pixmap = this->grab();
    QImage image = pixmap.toImage();

    cout << "[DEBUG] Image W=" << image.width()
         << ", H=" << image.height() << endl;

    const int WINDOW_SIZE = 50;
    const int STEP_SIZE = 5;
    int windowCount = 0;

    qDebug() << "Mulai analisis window (size:" << WINDOW_SIZE
             << ", step:" << STEP_SIZE << ")";

    for (int y = 0; y <= image.height() - WINDOW_SIZE; y += STEP_SIZE) {
        for (int x = 0; x <= image.width() - WINDOW_SIZE; x += STEP_SIZE) {

            QRect windowRect(x, y, WINDOW_SIZE, WINDOW_SIZE);
            QImage window = image.copy(windowRect);

            int nonWhiteCount = 0;
            if (isWindowNonEmpty(window, nonWhiteCount)) {
                windowCount++;

                if (windowCount % 50 == 0) {
                    qDebug() << "Cek Window ke-" << windowCount
                             << " di (" << x << "," << y << ")";
                }

                if (checkSegmentPattern(window)) {
                    m_candidateRegions.append(windowRect);
                }
            }
        }
    }

    qDebug() << "[INFO] Analisis selesai. Total kandidat terdeteksi:"
             << m_candidateRegions.size();

    update();
}

void DrawingCanvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen(Qt::blue, 5);
    painter.setPen(pen);
    painter.setBrush(Qt::blue);

    // Titik-titik yang digambar
    for (const QPoint& point : std::as_const(m_points)) {
        painter.drawEllipse(point, 3, 3);
    }

    // Jika tombol "Draw Lines" diklik
    if (isPaintLinesClicked) {
        pen.setColor(Qt::red);
        pen.setWidth(3);
        painter.setPen(pen);

        for (int i = 0; i + 1 < m_points.size(); i += 2) {
            painter.drawLine(m_points[i], m_points[i + 1]);
        }

        isPaintLinesClicked = false;
        pen.setColor(Qt::blue);
        painter.setPen(pen);
    }

    if (!m_candidateRegions.isEmpty()) {
        QPen rectPen(QColor(170, 0, 255), 2, Qt::DashLine);
        painter.setPen(rectPen);
        painter.setBrush(Qt::NoBrush);

        for (const QRect &rect : m_candidateRegions) {
            painter.drawRect(rect);
        }

        painter.setPen(Qt::darkMagenta);
        painter.drawText(10, 20,
                         QString("Kandidat terdeteksi: %1")
                             .arg(m_candidateRegions.size()));
    }
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event) {
    m_points.append(event->pos());
    update();
}



