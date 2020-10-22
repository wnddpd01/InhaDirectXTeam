#pragma once
class HeightMap
{
private:
	int m_size;
	int m_width;
	int m_height;
	vector<ST_PNT_VERTEX*> m_vecVertex;
	vector<ST_PNT_VERTEX> m_vecDrawVertex;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DMATERIAL9	m_stMtl;
	
public:
	HeightMap();
	~HeightMap();
	void LoadRaw(wstring rawFileName);
	void Setup(wstring rawFileName);
	void Render();

	float GetHeight(D3DXVECTOR3 pos);
};

