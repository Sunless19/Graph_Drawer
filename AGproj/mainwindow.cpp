#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,secondNode(nullptr)
    ,firstNode(nullptr)
    ,MousePressed(false)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent* e)
{
    if (e->button() == Qt::RightButton)
    {
        if (graf.verifyNodes(e))
            graf.addNode(e->pos());
        else
        {
            for (Node* n : graf.getNodes())
            {
                if (fabs(n->getX() - e->pos().x()) < Node::DimNode / 2.0 &&
                    fabs(n->getY() - e->pos().y()) < Node::DimNode / 2.0)
                    if (firstNode == nullptr)
                    {
                        firstNode = n;
                        firstNode->setIsSelected(true);
                    }
                    else
                    {
                        secondNode = n;
                        if (firstNode->getValue() != secondNode->getValue())
                        {
                            Arch* ed = new Arch(firstNode, secondNode);
                            if (graf.verifyArches(ed))
                                graf.addArch(ed);
                            else
                                delete ed;
                        }
                        firstNode->setIsSelected(false);
                        firstNode = nullptr;
                        secondNode = nullptr;
                    }
            }
        }
    }
    else
        if (e->button() == Qt::LeftButton)
        {
            for (Node* n : graf.getNodes())
            {
                if (fabs(n->getX() - e->pos().x()) < Node::DimNode / 2.0 &&
                    fabs(n->getY() - e->pos().y()) < Node::DimNode / 2.0)
                {
                    n->setIsSelected(true);
                    MousePressed = true;
                    break;
                }
            }
        }
    update();
}

void MainWindow::mouseMoveEvent(QMouseEvent* e)
{
    if (MousePressed)
        if (Qt::LeftButton)
        {
            for (Node* n : graf.getNodes())
                if (n->getIsSelected())
                {
                    if (graf.verifyNodes(e))
                        n->setCoordinate(e->pos());
                }
            update();
        }
}
void MainWindow::mouseReleaseEvent(QMouseEvent* e)
{
    if (e->button() == Qt::LeftButton)
    {
        MousePressed = false;
        for (Node* n : graf.getNodes())
        {
            n->setIsSelected(false);
        }
    }
}

void MainWindow::paintNode(QPainter& p, Node* n)
{
    if (n->getIsSelected())
        p.setPen(Qt::red);
    else
        p.setPen(Qt::black);

    QRect r(n->getX() - Node::DimNode / 2, n->getY() - Node::DimNode / 2, Node::DimNode, Node::DimNode);
    p.drawEllipse(r);
    QString s;
    s.setNum(n->getValue());
    p.drawText(r, Qt::AlignCenter, s);
}

void MainWindow::ClickedButton()
{
    if (graf.isOrientedOrNot())
    {
        if (ui->radioButton1->isChecked())
            graf.saveMatrixOriented();
        else
            if (ui->radioButton2->isChecked())
            {
                graf.setOrientedOrNot(false);
                graf.reset();
            }
    }
    else
    {
        if (ui->radioButton1->isChecked())
        {
            graf.setOrientedOrNot(true);
            graf.reset();
        }
        else
            if (ui->radioButton2->isChecked())
                graf.saveMatrixUnoriented();
    }
}

void MainWindow::drawLine(Node* N1, Node* N2, int radius, QPainter& p)
{
    p.setPen(Qt::black);
    qreal dx = N2->getX() - N1->getX();
    qreal dy = N2->getY() - N1->getY();
    qreal distance = qSqrt(dx * dx + dy * dy);
    qreal x1_intersec = N1->getX() + (dx * radius / distance);
    qreal y1_intersec = N1->getY() + (dy * radius / distance);
    qreal x2_intersec = N2->getX() - (dx * radius / distance);
    qreal y2_intersec = N2->getY() - (dy * radius / distance);

    p.drawLine(x1_intersec, y1_intersec, x2_intersec, y2_intersec);

    if (graf.isOrientedOrNot())
        drawArrow(QPoint(x1_intersec, y1_intersec), QPoint(x2_intersec, y2_intersec), p);
}

void MainWindow::drawArrow(QPoint Q1, QPoint Q2, QPainter& p)
{
    qreal arrowSize = Node::DimNode / 2.0;
    p.setBrush(Qt::black);
    QLineF line(Q2, Q1);

    double angle = std::atan2(-line.dy(), line.dx());
    QPointF arrowP1 = line.p1() + QPointF(sin(angle + M_PI / 3) * arrowSize, cos(angle + M_PI / 3) * arrowSize);
    QPointF arrowP2 = line.p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize, cos(angle + M_PI - M_PI / 3) * arrowSize);

    QPolygonF arrowHead;
    arrowHead.clear();
    arrowHead << line.p1() << arrowP1 << arrowP2;
    p.drawPolygon(arrowHead);

    p.setBrush(Qt::white);
}

void MainWindow::paintEvent(QPaintEvent* e)
{
    QPainter p(this);
    for (Node* n : graf.getNodes())
        paintNode(p, n);

    for (Arch* ed : graf.getArches())
        drawLine(ed->getFirstNode(), ed->getSecondNode(), Node::DimNode / 2, p);

   ClickedButton();
    update();
}



































//void MainWindow::paintEvent(QPaintEvent* e)
//{
//    QPainter p(this);
//    std::vector<Node> noduri = graf.getNodes();
//    for (Node& n : noduri)
//    {
//        QRect r(n.getX() - 25, n.getY() - 25, 50, 50);
//        p.drawEllipse(r);
//        QString s;
//        s.setNum(n.getValue());
//        p.drawText(r, Qt::AlignCenter, s);
//    }
//    std::vector<Arch> arches = graf.getArches();
//    for (Arch& a : arches)
//    {
//        p.drawLine(a.getFirstNode().getX(), a.getFirstNode().getY(),
//            a.getSecondNode().getX(), a.getSecondNode().getY());
//    }
//    if (firstNode.getValue() >= 0)
//    {
//        QRect r(firstNode.getX() - 25, firstNode.getY() - 25, 50, 50);
//        QPen pen;
//        pen.setColor(Qt::red);
//        pen.setWidth(2);
//        p.setPen(pen);
//        p.drawEllipse(r);
//        QString s;
//        s.setNum(firstNode.getValue());
//        p.drawText(r, Qt::AlignCenter, s);
//    }
//
//}
