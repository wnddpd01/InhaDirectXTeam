#include "stdafx.h"
#include "Astar.h"
#include "Node.h"

Astar::Astar()
{
}


Astar::~Astar()
{
}

void Astar::LoadNode()
{
	m_pNode.clear();

	gJSON->LoadJSON("Resource/json/Node.json");
	Value& documentValue = gJSON->mDocument["Node"];

	for (SizeType i = 0; i < documentValue.Size(); ++i)
	{
		D3DXVECTOR3 vec;
		vec.x = documentValue[i]["Position"]["PositionX"].GetDouble();
		vec.y = 0.0f;
		vec.z = documentValue[i]["Position"]["PositionZ"].GetDouble();

		Node* node = new Node;
		node->SetNodePoint(vec);
		m_pNode.push_back(node);
	}

	for (SizeType i = 0; i < documentValue.Size(); ++i)
	{
		Value& pathValue = documentValue[i]["Path"];

		for (SizeType j = 0; j < pathValue.Size(); ++j)
		{
			D3DXVECTOR3 vec;
			vec.x = pathValue[j]["PathX"].GetDouble();
			vec.y = 0.0f;
			vec.z = pathValue[j]["PathZ"].GetDouble();

			for (size_t k = 0; k < m_pNode.size(); ++k)
			{
				if (fabs(m_pNode[k]->GetNodePoint().x - vec.x) < 0.49f && fabs(m_pNode[k]->GetNodePoint().z - vec.z) < 0.49f)
				{
					Node::ConnectNodePoint(m_pNode[k], m_pNode[i]);
				}
			}
		}
	}
}
