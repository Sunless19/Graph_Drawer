#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QMouseEvent>
#include<QPaintEvent>
#include<QMainWindow>
#include "node.h"
#include "graph.h"
#include "ui_AGproj.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   
    virtual void mousePressEvent(QMouseEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* e);
    virtual void mouseMoveEvent(QMouseEvent* e);
    virtual void paintEvent(QPaintEvent* e);
    void drawLine(Node* N1, Node* N2, int radius, QPainter& p);
    void drawArrow(QPoint Q1, QPoint Q2, QPainter& p);
    void paintNode(QPainter&, Node*);

protected slots:
    void ClickedButton();

private:
    Ui::MainWindow *ui;
    Graph graf;
    Node* firstNode;
    Node* secondNode;
    QPoint offset;
    bool MousePressed;
    
};
#endif // MAINWINDOW_H
