#pragma once
class cCubePC
{
public:
	cCubePC();
	~cCubePC();
private:
	std::vector<ST_PC_VERTEX>	m_vecVertex;
	float						m_fRotY;
	D3DXVECTOR3					m_vDirection;
	D3DXVECTOR3					m_vPosition;
	D3DXMATRIXA16				m_matWorld;
public:
	void Setup();
	void Update(D3DXMATRIXA16* m_pWorld);
	void Render();
	D3DXVECTOR3& GetPosition();

	float sx, sy, sz;
	float tx, ty, tz;
	float ry;

	void SetTrans(float x, float y, float z);
	void SetScling(float x, float y, float z);
	void SetRotation(float x);

	D3DXMATRIXA16 GetWorld()
	{
		return m_matWorld;
	}

};
