#pragma once
#include "iMap.h"
class cHeightMap :
	public iMap
{
public:
	cHeightMap();
	virtual ~cHeightMap(void);

private :
	LPD3DXMESH				m_pMesh;
	vector<D3DXVECTOR3>		m_vecVertex;
	D3DMATERIAL9			m_stMtl;
	LPDIRECT3DTEXTURE9		m_pTexture;
	int						m_nTileNum;

public :
	void Setup(char* szFolder, char * szRaw, char* szTex, DWORD dwBytesPerPixel = 1);
	virtual void Render() override;
	virtual bool GetHeight(IN float x, OUT float & y, IN float z) override;
	void Destroy();
};

