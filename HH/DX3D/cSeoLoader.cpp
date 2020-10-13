#include "stdafx.h"
#include "cSeoLoader.h"
#include "cGeomObject.h"


cSeoLoader::cSeoLoader()
{
}


cSeoLoader::~cSeoLoader()
{
}

void cSeoLoader::Load(OUT std::vector<cGeomObject*>& vecGeomObject, IN char * szFolder, IN char * szFile)
{
	std::vector<D3DXVECTOR3> vecV;
	std::vector<D3DXVECTOR2> vecVT;
	std::vector<D3DXVECTOR3> vecVN;
	std::vector<ST_PNT_VERTEX> vecVertex;

	std::string sFullPath(szFolder);
	sFullPath += (std::string("/") + std::string(szFile));

	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	std::string  sMtlName;
	while (true)
	{
		if (feof(fp)) break;

		char szTemp[1024];
		fgets(szTemp, 1024, fp);
		std::string stTemp(szTemp);
		
		if (stTemp == "*GEOMOBJECT {\n")
		{
			cGeomObject* pGeomTemp = new cGeomObject;
			while (true)
			{
				fgets(szTemp, 1024, fp);
				std::string stTemp;

				char szGeoTemp[1024];
				sscanf_s(szTemp, "%s", szGeoTemp, 1024);
				stTemp = std::string(szGeoTemp);

				if (stTemp == "}")
				{
					vecGeomObject.push_back(pGeomTemp);
					break;
				}
				else if (stTemp == "*NODE_NAME")
				{
					sscanf_s(szTemp, "%*s %s", &szGeoTemp, 1024);
					pGeomTemp->m_nodeName = std::string(szGeoTemp);
				}
				else if (stTemp == "*NODE_PARENT")
				{
					sscanf_s(szTemp, "%*s %s", &szGeoTemp, 1024);
					pGeomTemp->m_nodeParant = std::string(szGeoTemp);
				}
				else if (stTemp == "*NODE_TM")
				{
					while (true)
					{
						fgets(szTemp, 1024, fp);
						std::string stTemp;
						char szMeshTemp[1024];
						sscanf_s(szTemp, "%s", &szMeshTemp ,1024);
						stTemp = std::string(szMeshTemp);

						if (stTemp == "}")
						{
							
							break;
						}
					}

				}
				else if (stTemp == "*MESH")
				{
					while (true)
					{
						fgets(szTemp, 1024, fp);
						std::string stTemp;
						char szMeshTemp[1024];
						sscanf_s(szTemp, "%s", &szMeshTemp, 1024);
						stTemp = std::string(szMeshTemp);

						if (stTemp == "}")
						{
							break;
						}
						else if (stTemp == "*TIMEVALUE")
						{
							sscanf_s(szTemp, "%*s %d", &pGeomTemp->m_geoMesh.timeValue);
						}
						else if (stTemp == "*MESH_NUMVERTEX")
						{
							sscanf_s(szTemp, "%*s %d", &pGeomTemp->m_geoMesh.NumVertex);
							vecV.resize(pGeomTemp->m_geoMesh.NumVertex);
						}
						else if (stTemp == "*MESH_NUMFACES")
						{
							sscanf_s(szTemp, "%*s %d", &pGeomTemp->m_geoMesh.NumFaces);
							pGeomTemp->m_geoMesh.vecVertex.resize(pGeomTemp->m_geoMesh.NumFaces*3);
						}
						else if (stTemp == "*MESH_VERTEX_LIST")
						{
							for (int i = 0; i < vecV.size(); i++)
							{
								fgets(szTemp, 1024, fp);
								std::string stTemp;
								sscanf_s(szTemp, "%*s %*s %f %f %f", &vecV[i].x, &vecV[i].z, &vecV[i].y);
							}
							fgets(szTemp, 1024, fp);
						}
						else if (stTemp == "*MESH_FACE_LIST")
						{
							for( int i = 0; i < pGeomTemp->m_geoMesh.vecVertex.size(); i+=3)
							{
								fgets(szTemp, 1024, fp);
								std::string stTemp;
								int x, y, z;
								sscanf_s(szTemp, "%*s %*s %*s %d %*s %d %*s %d", &x, &y, &z);
								pGeomTemp->m_geoMesh.vecVertex[i].p = vecV[x];
								pGeomTemp->m_geoMesh.vecVertex[i+1].p = vecV[y];
								pGeomTemp->m_geoMesh.vecVertex[i+2].p = vecV[z];
							}
							fgets(szTemp, 1024, fp);
						}
						else if (stTemp == "*MESH_NUMTVERTEX")
						{
							
						}
						else if (stTemp == "*MESH_NORMALS")
						{
							while (true)
							{
								fgets(szTemp, 1024, fp);
								std::string stTemp;
								char szMeshTemp[1024];
								sscanf_s(szTemp, "%s", &szMeshTemp, 1024);
								stTemp = std::string(szMeshTemp);

								if (stTemp == "}")
								{
									break;
								}
							}
						}
					}
				}
				else if (stTemp == "*PROP_MOTIONBLUR")
				{
					sscanf_s(szTemp, "%*s %d", &pGeomTemp->m_motionBlur);
				}
				else if (stTemp == "*PROP_CASTSHADOW")
				{
					sscanf_s(szTemp, "%*s %d", &pGeomTemp->m_motionBlur);
				}
				else if (stTemp == "*PROP_RECVSHADOW")
				{
					sscanf_s(szTemp, "%*s %d", &pGeomTemp->m_motionBlur);
				}
				else if (stTemp == "*TM_ANIMATION")
				{
					while (true)
					{
						fgets(szTemp, 1024, fp);
						std::string stTemp;
						char szMeshTemp[1024];
						sscanf_s(szTemp, "%s", &szMeshTemp, 1024);
						stTemp = std::string(szMeshTemp);

						if (stTemp == "}")
						{
							break;
						}
						else if (stTemp == "*CONTROL_POS_TRACK")
						{
							while (true)
							{
								fgets(szTemp, 1024, fp);
								std::string stTemp;
								char szMeshTemp[1024];
								sscanf_s(szTemp, "%s", &szMeshTemp, 1024);
								stTemp = std::string(szMeshTemp);

								if (stTemp == "}")
								{
									break;
								}
							}
						}
						else if (stTemp == "*CONTROL_ROT_TRACK")
						{
							while (true)
							{
								fgets(szTemp, 1024, fp);
								std::string stTemp;
								char szMeshTemp[1024];
								sscanf_s(szTemp, "%s", &szMeshTemp, 1024);
								stTemp = std::string(szMeshTemp);

								if (stTemp == "}")
								{
									break;
								}
							}
						}
					}
				}
			}
		}
	}
	fclose(fp);
	
	/*
	for each(auto it in m_mapMtlTex)
	{
		SafeRelease(it.second);
	}
	m_mapMtlTex.clear();
	*/
}

void cSeoLoader::LoadMtlLib(char * szFolder, char * szFile)
{
}
