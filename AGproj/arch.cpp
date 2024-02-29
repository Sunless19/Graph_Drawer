#include "arch.h"

Arch::Arch() 
	:firstNode{nullptr},
	secondNode{nullptr}
{
}

Arch::Arch(Node* n1, Node* n2)
{
	firstNode = n1;
	secondNode = n2;
}

Arch::~Arch()
{
}

Node* Arch::getFirstNode()
{
	return firstNode;
}

Node* Arch::getSecondNode()
{
	return secondNode;
}


