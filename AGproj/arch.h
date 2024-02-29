#ifndef ARCH_H
#define ARCH_H

#include "node.h"

class Arch
{
private:
    Node* firstNode, *secondNode;
public:
    Arch();
    Arch(Node* , Node* );
    ~Arch();
    Node* getFirstNode();
    Node* getSecondNode();
};

#endif // ARCH_H
