#pragma 
class MapObjectCenter;

class MapObject
{
protected:
	MapObjectCenter* m_pObjCenter;
	LPD3DXMESH m_pMesh;
	D3DXVECTOR3 m_pos;
	D3DMATERIAL9 m_mtl;
	bool m_boolMtl;
	D3DMATERIAL9 m_arrMtl[2];
	float m_collisionSize;
	
public:
	MapObject(MapObjectCenter* pCenter);
	virtual ~MapObject();
	virtual void Setup() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	void ToggleMtl();

	float GetCollisionSize();
	D3DXVECTOR3 GetPos();
};

