#include "mainwindow.h"
#include "drawingcanvas.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Create a central widget to hold the layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout *subLayout = new QHBoxLayout();

    // Create and add the drawing canvas to the top of the layout
    DrawingCanvas *m_canvas = new DrawingCanvas(this);
    mainLayout->addWidget(m_canvas);

    // Create buttons
    m_clearButton = new QPushButton("Clear Canvas", this);
    m_detectButton = new QPushButton("Detect Segment", this);
    m_drawButton = new QPushButton("Draw Lines", this);

    // Add buttons to subLayout
    mainLayout->addLayout(subLayout);
    subLayout->addWidget(m_drawButton);
    subLayout->addWidget(m_detectButton);
    subLayout->addWidget(m_clearButton);

    // Connect signals to slots
    connect(m_clearButton, &QPushButton::clicked, m_canvas, &DrawingCanvas::clearPoints);
    connect(m_drawButton, &QPushButton::clicked, m_canvas, &DrawingCanvas::paintLines);
    // KONEKSI PENTING untuk menjalankan deteksi
    connect(m_detectButton, &QPushButton::clicked, m_canvas, &DrawingCanvas::segmentDetection);

    // Set layout
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    setWindowTitle("Drawing Canvas");
}

MainWindow::~MainWindow()
{
}

