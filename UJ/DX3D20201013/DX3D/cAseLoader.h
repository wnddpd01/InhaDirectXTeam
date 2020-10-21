#pragma once

class cFrame;
class cMtlTex;

class cAseLoader
{
public:
	cAseLoader();
	~cAseLoader();

private :
	FILE * m_fp;
	char m_szToken[1024];
	vector<cMtlTex*>	m_vecMtlTex;
	vector<WORD>		m_vecAttr;
	map<string, cFrame*> m_mapFrame;

public :
	cFrame * Load(IN char* szFullPath);
	LPD3DXMESH LoadMesh(OUT vector<cMtlTex*>& vecMtlTex, IN char* szFullPath);
private :
	char*	GetToken();
	int		GetInteger();
	float	GetFloat();
	bool	IsWhite(IN char c);
	bool	IsEqual(IN char * str1, IN char * str2);
	void	SkipBlock();
	void	Process_MATERIAL_LIST();
	void	Process_MATERIAL(OUT cMtlTex* pMtlTex);
	void	Process_MAP_DIFFUSE(OUT cMtlTex* pMtlTex);
	cFrame*	Process_GEOMOBJECT();
	void	Process_MESH(OUT cFrame* pFrame);
	void	Process_MESH_VERTEX_LIST(OUT vector<D3DXVECTOR3>& vecV);
	void	Process_MESH_FACE_LIST(OUT vector<ST_PNT_VERTEX>& vecVertex, IN vector<D3DXVECTOR3>& vecV);
	void	Process_MESH_TVERT_LIST(OUT vector<D3DXVECTOR2>& vecVT);
	void	Process_MESH_TFACE_LIST(OUT vector<ST_PNT_VERTEX>& vecVertex, IN vector<D3DXVECTOR2>& vecVT);
	void	Process_MESH_NORMALS(OUT vector<ST_PNT_VERTEX>& vecVertex);
	void	Process_NODE_TM(OUT cFrame* pFrame);
	void	Process_TM_ANIMATION(OUT cFrame*);
	void	Process_CONTROL_POS_TRACK(OUT cFrame* pFrame);
	void	Process_CONTROL_ROT_TRACK(OUT cFrame* pFrame);
	void	Process_Scene();
	void	Set_SceneFrame(OUT cFrame* pRoot);

	DWORD	m_dwFirstFrame;
	DWORD	m_dwLastFrame;
	DWORD	m_dwFrameSpeed;
	DWORD	m_dwTicksPerFrame;
};

