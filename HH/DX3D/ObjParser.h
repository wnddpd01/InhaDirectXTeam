#pragma once
class ObjParser
{
private:

	std::vector<ST_PNT_VERTEX>	m_vecVertex;
	D3DMATERIAL9				m_stMtl;
	LPDIRECT3DTEXTURE9			m_pTexture;
	std::string					m_strMtlName;
	std::wstring				m_wstrTextureName;
	
	
public:
	ObjParser();
	~ObjParser();

	void Setup(std::string fileName);
	void Render();
	void Update();
};

