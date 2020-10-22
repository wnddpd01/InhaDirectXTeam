#pragma once
class PickingMap
{
	vector<ST_PNT_VERTEX> m_vecMap;
	ST_PNT_VERTEX m_Point;
	LPD3DXMESH	BoxMesh;
	
public:
	PickingMap();
	~PickingMap();

	void SetupBoard();
	void RenderBoard();

	vector<ST_PNT_VERTEX>& GetVecMap();
	D3DXVECTOR3 GetWayPoint();
	void SetWayPoint(D3DXVECTOR3 pos);
	
	
};

