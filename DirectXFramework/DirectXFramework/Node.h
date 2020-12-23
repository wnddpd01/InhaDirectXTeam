#pragma once

class Node
{
public:
	Node();
	~Node();

	void SetNodePoint(D3DXVECTOR3 position);
	D3DXVECTOR3 GetNodePoint() { return mPosition; }
	static void ConnectNodePoint(Node* node1, Node* node2);
	
private:
	map<float,Node*> mPath;
	D3DXVECTOR3 mPosition;
};

