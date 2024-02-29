#ifndef NODE_H
#define NODE_H

#include <QPainter>
class Node
{
    int value;
    QPoint coordinate;
    bool isSelected;
public:
    Node();
    Node(QPoint, int);
    Node(Node*);
    ~Node();
    void setValue(int value);
    void setCoordinate(QPoint);
    void setNode(Node* val);
    void setIsSelected(bool);
    void setCoordinate(int x, int y);
    QPoint getCoordinate();
    int getValue();
    int getX();
    int getY();
    bool getIsSelected();
    static const int DimNode = 50;
};

#endif // NODE_H
