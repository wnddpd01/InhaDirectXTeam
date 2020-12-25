#pragma once
#include <set>
class Node;

class Astar
{
public:
	Astar();
	~Astar();
	
	void LoadNode();
	void CreatePath();
	vector<D3DXVECTOR3> GetPath() { return mPath; }
	
	void	FindPath();
	Node*	FindNode(Node::eNodeType e);
	float	CalcHeuristic(Node* pNode1, Node* pNode2);
	Node*	GetMinFNodeAtOpenList();
	void	Extend(Node* pCurrNode, Node* pDestNode);
	Node*	GetAdjNode(Node* pCurrNode);
	bool	IsInList(Node* pNode, std::set<Node*>& setNodeList);
	void	MarkNodeType(Node* pDestNode);
	
private:
	vector<D3DXVECTOR3> mPath;
	vector<Node*> m_pNode;

	float		m_fF;
	float		m_fG;
	float		m_fH;
	bool		m_isClosed;
	
};

