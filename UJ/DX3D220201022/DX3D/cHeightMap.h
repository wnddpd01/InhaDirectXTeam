#pragma once
#include <thread>

#include "iMap.h"
class cHeightMap :
	public iMap
{
public:
	cHeightMap();
	virtual ~cHeightMap(void);

private :
	LPD3DXMESH				m_pMesh;
	D3DMATERIAL9			m_stMtl;
	LPDIRECT3DTEXTURE9		m_pTexture;
	int						m_nTileNum;
	thread                  m_thread;
public :
	void BuildThreadCall(D3DXPLANE * planes = NULL);
	void BuildMesh(D3DXPLANE * planes = NULL);
	vector<D3DXVECTOR3>		m_vecVertex;
	vector<ST_PNT_VERTEX>	m_vecPNTVertex;
	set<size_t> m_setNotDrawIdx;
	void Setup(char* szFolder, char * szRaw, char* szTex, DWORD dwBytesPerPixel = 1);
	virtual void Render() override;
	virtual bool GetHeight(IN float x, OUT float & y, IN float z) override;
	void Destroy();
};

