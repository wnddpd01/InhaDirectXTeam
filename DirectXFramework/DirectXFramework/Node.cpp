#include "stdafx.h"
#include "Node.h"


Node::Node()
	: mPosition(0,0,0)
{
}

Node::~Node()
{
}

void Node::SetNodePoint(D3DXVECTOR3 position)
{
	mPosition = position;
}

void Node::ConnectNodePoint(Node * node1, Node * node2)
{
	FLOAT length;
	length = D3DXVec3Length(&(node1->GetNodePoint() - node2->GetNodePoint()));
	node1->mPath.insert(make_pair(length, node2));
	node2->mPath.insert(make_pair(length, node1));
}
