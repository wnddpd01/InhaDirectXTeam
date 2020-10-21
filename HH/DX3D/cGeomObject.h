#pragma once
class cGeomObject
{
public:
	std::string m_nodeName;
	std::string m_nodeParant;
	std::vector<cGeomObject*> m_vecChild;

	GeoNodeTm m_geoNodeTm;
	GeoMesh m_geoMesh;

	bool m_motionBlur;
	bool m_castShadow;
	bool m_recvShadow;
	int		mtl_ref;

	D3DXVECTOR3 m_wireFrameColor;
	GeoAnimation m_GeoAnimation;

public:
	cGeomObject();
	~cGeomObject();

	cGeomObject* GetInstance(std::string nodeName);
	void Render();
	void InverseAllMesh();

};

