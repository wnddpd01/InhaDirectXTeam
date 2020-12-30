#include "stdafx.h"
#include "Node.h"


Node::Node()
	: mPosition(0, 0, 0)
	, mF(0.0f)
	, mG(0.0f)
	, mH(0.0f)
	, mParent(nullptr)
	, mIsClosed(false)
{
}

Node::~Node()
{
}

void Node::ConnectNodePoint(Node * node1, Node * node2)
{
	node1->mPath.push_back(node2);
	node2->mPath.push_back(node1);	
}
