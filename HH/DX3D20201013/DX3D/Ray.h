#pragma once
class MapObject;

class Ray
{
private:
	D3DXVECTOR3 m_vStart;
	D3DXVECTOR3 m_vDir;
	
public:
	Ray();
	~Ray();
	void SetDir(D3DXVECTOR3 dir);
	void SetStart(D3DXVECTOR3 start);
	bool CheckCollisionMesh(MapObject& mapObj);
	void CheckCollisionBoard(PickingMap& pickingMap);
};

