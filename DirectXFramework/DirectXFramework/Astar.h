#pragma once
class Node;

class Astar
{
public:
	Astar();
	~Astar();
	
	void LoadNode();
	void SearchPath();
	vector<D3DXVECTOR3> GetPath() { return mPath; }

private:
	vector<D3DXVECTOR3> mPath;
	vector<Node*> m_pNode;
};

