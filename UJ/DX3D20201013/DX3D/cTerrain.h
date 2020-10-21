#pragma once
class cTerrain
{
	LPDIRECT3DTEXTURE9 m_texture;
	vector<ST_PNT_VERTEX> m_vecVertex;
	LPD3DXMESH		   m_mesh;
public:
	float m_arrMapVertex[257][257];
	cTerrain();
	~cTerrain();
	static cTerrain * LoadFromRawFile(char *fileDir);
	void SetTextureFromFile(char *fileDir);
	void Render();
};

