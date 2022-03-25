#ifndef STARRYWINDOW_H
#define STARRYWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class starryWindow : public QWidget
{
    Q_OBJECT
public:
    starryWindow();
    starryWindow(QWidget*);
    void setBorderRadius(int r);
    void addBackground(QVector<QString>); // 设置背景图片
    void changeBackground(int); // 更换指定背景图片
    void changeBackground(); // 随机更换背景图片
    void setBorderRadius(int, int);
    void updateBorderRadius();
    // 拖曳操作
    bool m_move = false;
    QPoint m_startPoint;
    QPoint m_windowPoint;

private:
    QVector<QString> bg;
    float opaticy=0.95;
    int borderRadius=20;



protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
};

#endif // STARRYWINDOW_H
