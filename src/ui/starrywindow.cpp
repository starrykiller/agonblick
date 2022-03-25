#include "starrywindow.h"
#include "qdebug.h"
#include "qevent.h"
#include <QBitmap>
#include <QPainter>
#include <QRandomGenerator64>

starryWindow::starryWindow()
{
    // 基本UI操作
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowOpacity(this->opaticy);

    //设置窗体为圆角
    updateBorderRadius();
}

starryWindow::starryWindow(QWidget* parent) {
    // 基本UI操作
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowOpacity(this->opaticy);

    //设置窗体为圆角
    updateBorderRadius();
}

void starryWindow::addBackground(QVector<QString> img) {
    // 设置背景(覆盖)
    this->bg=img;
    changeBackground();
}

void starryWindow::changeBackground() {
    if (bg.size()==0) return;
    int bgid = QRandomGenerator64::global()->bounded(0,bg.size());
    qDebug() << "Changing to background " << bgid;
    QPixmap pixmap = QPixmap(bg[bgid]).scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    setPalette(palette);
}

void starryWindow::changeBackground(int pic) {
    if (bg.size()==0||pic>bg.size()) return;
    qDebug() << "Changing to background " << pic;
    QPixmap pixmap = QPixmap(bg[pic]).scaled(this->size());
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Background, QBrush(pixmap));
    setPalette(palette);
}

void starryWindow::updateBorderRadius() {
    qDebug() << "Updating Border Radius to " << borderRadius;
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(), borderRadius, borderRadius);
    setMask(bmp);
}

void starryWindow::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_move = true;
        m_startPoint = event->globalPos();
        m_windowPoint = this->frameGeometry().topLeft();
    }
}

void starryWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        QPoint relativePos = event->globalPos() - m_startPoint;
        this->move(m_windowPoint + relativePos);
    }
}

void starryWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        m_move = false;
    }
}

