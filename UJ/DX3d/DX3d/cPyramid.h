#pragma once
class cPyramid
{
public:
	cPyramid();
	~cPyramid();

private :
	vector<ST_PC_VERTEX> m_vecVertex;
	D3DXMATRIXA16		 m_matR;
	D3DXVECTOR3			 m_vecPosition;
public :
	void Setup(D3DCOLOR c, D3DXMATRIXA16& mat);
	void SetPosition(D3DXVECTOR3& newPos);
	void Render();
};

