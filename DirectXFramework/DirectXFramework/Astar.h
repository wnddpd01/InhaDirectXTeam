#pragma once
#include <set>
#include "Node.h"
class Node;

class Astar
{
public:
	Astar();
	~Astar();
	
	void LoadNode();

	vector<D3DXVECTOR3> FindPath(Node * startNode, Node * destNode);

	FLOAT CalcHeuristic(Node* pNode1, Node* pNode2);
	Node*	GetMinFNodeAtOpenList();
	void	Extend(Node* pCurrNode, Node* pDestNode);
	bool	IsInList(Node* pNode, std::set<Node*>& setNodeList);
	
private:
	vector<D3DXVECTOR3> mPath;
	vector<Node*> mNode;
	set<Node*>	mSetOpenList;
	set<Node*>	mSetCloseList;	
};

