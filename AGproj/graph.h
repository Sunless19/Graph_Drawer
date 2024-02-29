#ifndef GRAPH_H
#define GRAPH_H

#include "arch.h"
#include "node.h"
#include <vector>
#include <QMouseEvent>
#include <fstream>

class Graph
{
    std::vector<Node*> m_nodes;
    std::vector<Arch*> m_arches;
    bool isOriented;
public:
    Graph();
    Graph(Graph& g);
    ~Graph();
    void addNode(Node* n);
    void addNode(QPoint p);
    void addArch(Arch*);
    void addArch(Node*, Node*);
    void setOrientedOrNot(bool);

    std::vector<Node*> getNodes();
    std::vector<Arch*> getArches();
    Node* GetNod(QMouseEvent* e);
    bool isOrientedOrNot();

    bool verifyNodes(QMouseEvent* e);
    bool verifyArches(Arch* ed);

    void saveMatrixUnoriented();
    void saveMatrixOriented();
    void reset();

};

#endif // GRAPH_H
