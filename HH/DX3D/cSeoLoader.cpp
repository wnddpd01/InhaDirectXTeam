#include "stdafx.h"
#include "cSeoLoader.h"
#include "cSeoGroup.h"
#include "cGeomObject.h"


cSeoLoader::cSeoLoader()
{
}


cSeoLoader::~cSeoLoader()
{
}

void cSeoLoader::Load(OUT std::vector<cSeoGroup*>& vecSeoGroup, IN char * szFolder, IN char * szFile)
{
	cSeoGroup* pSeoGroup = new cSeoGroup;
	
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
		if (feof(fp))
		{
			vecSeoGroup.push_back(pSeoGroup);
			break;
		}

		char szTemp[1024];
		fgets(szTemp, 1024, fp);
		std::string stTemp(szTemp);
		if (stTemp == "*SCENE {\n")
		{
			while (true)
			{
				fgets(szTemp, 1024, fp);
				std::string stTemp;

				char szGeoTemp[1024];
				sscanf_s(szTemp, "%s", szGeoTemp, 1024);
				stTemp = std::string(szGeoTemp);

				if (stTemp == "}")
				{
					break;
				}
				else if (stTemp == "*SCENE_FILENAME")
				{
					sscanf_s(szTemp, "%*s %s", &szGeoTemp, 1024);
					pSeoGroup->m_scene.FileName = std::string(szGeoTemp);
				}
				else if (stTemp == "*SCENE_FIRSTFRAME")
				{
					sscanf_s(szTemp, "%*s %d",
						&pSeoGroup->m_scene.FirstFrame);
				}
				else if (stTemp == "*SCENE_LASTFRAME")
				{
					sscanf_s(szTemp, "%*s %d",
						&pSeoGroup->m_scene.LastFrame);
				}
				else if (stTemp == "*SCENE_FRAMESPEED")
				{
					sscanf_s(szTemp, "%*s %d",
						&pSeoGroup->m_scene.FrameSpeed);
				}
				else if (stTemp == "*SCENE_TICKSPERFRAME")
				{
					sscanf_s(szTemp, "%*s %d",
						&pSeoGroup->m_scene.TickSperFrame);
				}
				else if (stTemp == "*SCENE_BACKGROUND_STATIC")
				{
					sscanf_s(szTemp, "%*s %f %f %f",
						&pSeoGroup->m_scene.BackGraound_Static.x,
						&pSeoGroup->m_scene.BackGraound_Static.y, 
						&pSeoGroup->m_scene.BackGraound_Static.z);
				}
				else if (stTemp == "*SCENE_AMBIENT_STATIC")
				{
					sscanf_s(szTemp, "%*s %f %f %f",
						&pSeoGroup->m_scene.BackGraound_Static.x,
						&pSeoGroup->m_scene.BackGraound_Static.y,
						&pSeoGroup->m_scene.BackGraound_Static.z);
				}
			}
		}
		else if (stTemp == "*MATERIAL_LIST {\n")
		{
			
			while (true)
			{
				fgets(szTemp, 1024, fp);
				std::string stTemp;

				char szGeoTemp[1024];
				sscanf_s(szTemp, "%s", szGeoTemp, 1024);
				stTemp = std::string(szGeoTemp);

				if (stTemp == "}")
				{
					break;
				}
				else if (stTemp == "*MATERIAL")
				{
					Material* pTempMtl = new Material;
					while (true)
					{
						fgets(szTemp, 1024, fp);
						std::string stTemp;

						char szGeoTemp[1024];
						sscanf_s(szTemp, "%s", szGeoTemp, 1024);
						stTemp = std::string(szGeoTemp);

						if (stTemp == "}")
						{
							pSeoGroup->m_vecMtlObject.push_back(pTempMtl);
							break;
						}
						else if (stTemp == "*MATERIAL_NAME")
						{
							sscanf_s(szTemp, "%*s %s", &szGeoTemp, 1024);
							pTempMtl->Name = std::string(szGeoTemp);
						}
						else if (stTemp == "*MATERIAL_CLASS")
						{
							sscanf_s(szTemp, "%*s %s", &szGeoTemp, 1024);
							pTempMtl->Name = std::string(szGeoTemp);
						}
						else if (stTemp == "*MATERIAL_AMBIENT")
						{
							sscanf_s(szTemp, "%*s %f %f %f",
								&pTempMtl->Ambient.x,
								&pTempMtl->Ambient.y,
								&pTempMtl->Ambient.z);
						}
						else if (stTemp == "*MATERIAL_DIFFUSE")
						{
							sscanf_s(szTemp, "%*s %f %f %f",
								&pTempMtl->Diffuse.x,
								&pTempMtl->Diffuse.y,
								&pTempMtl->Diffuse.z);
						}
						else if (stTemp == "*MATERIAL_SPECULAR")
						{
							sscanf_s(szTemp, "%*s %f %f %f",
								&pTempMtl->Specular.x,
								&pTempMtl->Specular.y,
								&pTempMtl->Specular.z);
						}
						else if (stTemp == "*MATERIAL_SHINE")
						{
							sscanf_s(szTemp, "%*s %f",
								&pTempMtl->Shine);
						}
						else if (stTemp == "*MATERIAL_SHINESTRENGTH")
						{
							sscanf_s(szTemp, "%*s %f",
								&pTempMtl->ShineStrength);
						}
						else if (stTemp == "*MATERIAL_TRANSPARENCY")
						{
							sscanf_s(szTemp, "%*s %f",
								&pTempMtl->Transparency);
						}
						else if (stTemp == "*MATERIAL_WIRESIZE")
						{
							sscanf_s(szTemp, "%*s %f",
								&pTempMtl->WireSize);
						}
						else if (stTemp == "*MATERIAL_SHADING")
						{
							sscanf_s(szTemp, "%*s %s", &szGeoTemp, 1024);
							pTempMtl->Shading = std::string(szGeoTemp);
						}
						else if (stTemp == "*MATERIAL_XP_FALLOFF")
						{
							sscanf_s(szTemp, "%*s %f",
								&pTempMtl->Xp_Falloff);
						}
						else if (stTemp == "*MATERIAL_SELFILLUM")
						{
							sscanf_s(szTemp, "%*s %f",
								&pTempMtl->SelfIllum);
						}
						else if (stTemp == "*MATERIAL_FALLOFF")
						{
							sscanf_s(szTemp, "%*s %s", &szGeoTemp, 1024);
							pTempMtl->Falloff = std::string(szGeoTemp);
						}
						else if (stTemp == "*MATERIAL_XP_TYPE")
						{
							sscanf_s(szTemp, "%*s %s", &szGeoTemp, 1024);
							pTempMtl->XP_Type = std::string(szGeoTemp);
						}
						else if (stTemp == "*MAP_DIFFUSE")
						{
							while (true)
							{
								fgets(szTemp, 1024, fp);
								std::string stTemp;

								char szGeoTemp[1024];
								sscanf_s(szTemp, "%s", szGeoTemp, 1024);
								stTemp = std::string(szGeoTemp);

								if (stTemp == "}")
								{
									break;
								}
								else if (stTemp == "*MAP_NAME")
								{
									sscanf_s(szTemp, "%*s %s", &szGeoTemp, 1024);
									pTempMtl->structDiffuse.MapName = std::string(szGeoTemp);
								}
								else if (stTemp == "*MAP_CLASS")
								{
									sscanf_s(szTemp, "%*s %s", &szGeoTemp, 1024);
									pTempMtl->structDiffuse.MapClass = std::string(szGeoTemp);
								}
								else if (stTemp == "*MAP_SUBNO")
								{
									sscanf_s(szTemp, "%*s %d",
										&pTempMtl->structDiffuse.SubNo);
								}
								else if (stTemp == "*MAP_AMOUNT")
								{
									sscanf_s(szTemp, "%*s %f",
										&pTempMtl->structDiffuse.MapAmount);
								}
								else if (stTemp == "*BITMAP")
								{
									sscanf_s(szTemp, "%*s %s", &szGeoTemp, 1024);
									std::string temp(szGeoTemp);
									for (auto it : temp)
									{
										if (it != '\"')
											pTempMtl->structDiffuse.Bitmap.push_back(it);
									}
								}
								else if (stTemp == "*MAP_TYPE")
								{
									sscanf_s(szTemp, "%*s %s", &szGeoTemp, 1024);
									pTempMtl->structDiffuse.MapType = std::string(szGeoTemp);
								}
								else if (stTemp == "*UVW_U_OFFSET")
								{
									sscanf_s(szTemp, "%*s %f",
										&pTempMtl->structDiffuse.UVW_U_Offset);
								}
								else if (stTemp == "*UVW_V_OFFSET")
								{
									sscanf_s(szTemp, "%*s %f",
										&pTempMtl->structDiffuse.UVW_V_Offset);
								}
								else if (stTemp == "*UVW_U_TILING")
								{
									sscanf_s(szTemp, "%*s %f",
										&pTempMtl->structDiffuse.UVW_U_Tiling);
								}
								else if (stTemp == "*UVW_V_TILING")
								{
									sscanf_s(szTemp, "%*s %f",
										&pTempMtl->structDiffuse.UVW_V_Tiling);
								}
								else if (stTemp == "*UVW_ANGLE")
								{
									sscanf_s(szTemp, "%*s %f",
										&pTempMtl->structDiffuse.UVW_Angel);
								}
								else if (stTemp == "*UVW_BLUR")
								{
									sscanf_s(szTemp, "%*s %f",
										&pTempMtl->structDiffuse.UVW_Blur);
								}
								else if (stTemp == "*UVW_BLUR_OFFSET")
								{
									sscanf_s(szTemp, "%*s %f",
										&pTempMtl->structDiffuse.UVW_Blur_Offset);
								}
								else if (stTemp == "*UVW_NOUSE_AMT")
								{
									sscanf_s(szTemp, "%*s %f",
										&pTempMtl->structDiffuse.UVW_Nouse_Amt);
								}
								else if (stTemp == "*UVW_NOISE_SIZE")
								{
									sscanf_s(szTemp, "%*s %f",
										&pTempMtl->structDiffuse.UVW_Noise_Size);
								}
								else if (stTemp == "*UVW_NOISE_LEVEL")
								{
									sscanf_s(szTemp, "%*s %d",
										&pTempMtl->structDiffuse.UVW_Noise_Level);
								}
								else if (stTemp == "*UVW_NOISE_PHASE")
								{
									sscanf_s(szTemp, "%*s %f",
										&pTempMtl->structDiffuse.UVW_Noise_Phase);
								}
								else if (stTemp == "*BITMAP_FILTER")
								{
									sscanf_s(szTemp, "%*s %s", &szGeoTemp, 1024);
									pTempMtl->structDiffuse.Bitmap_Filter = std::string(szGeoTemp);
								}
							}
						}
					}
				}
			}
		}
		else if (stTemp == "*GEOMOBJECT {\n")
		{
			cGeomObject* pGeomTemp = new cGeomObject;
			while (true)
			{
				fgets(szTemp, 1024, fp);
				std::string stTemp;

				char szGeoTemp[1024];
				sscanf_s(szTemp, "%s", szGeoTemp, 1024);
				stTemp = std::string(szGeoTemp);

				if (stTemp == "*MATERIAL_REF")
					std::cout << std::endl;
				
				if (stTemp == "}")
				{
					pSeoGroup->m_vecGeomObject.push_back(pGeomTemp);
					break;
				}
				else if (stTemp == "*NODE_NAME")
				{
					sscanf_s(szTemp, "%*s %[^\n]", &szGeoTemp, 1024);
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
						else if (stTemp == "*INHERIT_POS")
						{
							sscanf_s(szTemp, "%*s %f %f %f", 
								&pGeomTemp->m_geoNodeTm.inheritPos.x
								, &pGeomTemp->m_geoNodeTm.inheritPos.z
								, &pGeomTemp->m_geoNodeTm.inheritPos.y);
						}
						else if (stTemp == "*INHERIT_ROT")
						{
							sscanf_s(szTemp, "%*s %f %f %f",
								&pGeomTemp->m_geoNodeTm.inheritRot.x
								, &pGeomTemp->m_geoNodeTm.inheritRot.z
								, &pGeomTemp->m_geoNodeTm.inheritRot.y);
						}
						else if (stTemp == "*INHERIT_SCL")
						{
							sscanf_s(szTemp, "%*s %f %f %f",
								&pGeomTemp->m_geoNodeTm.inheritScl.x
								, &pGeomTemp->m_geoNodeTm.inheritScl.z
								, &pGeomTemp->m_geoNodeTm.inheritScl.y);
						}
						else if (stTemp == "*TM_ROW0")
						{
							sscanf_s(szTemp, "%*s %f %f %f",
								&pGeomTemp->m_geoNodeTm.tmMat._11
								, &pGeomTemp->m_geoNodeTm.tmMat._13
								, &pGeomTemp->m_geoNodeTm.tmMat._12);
							pGeomTemp->m_geoNodeTm.tmMat._14 = 0.f;
						}
						else if (stTemp == "*TM_ROW2")
						{
							sscanf_s(szTemp, "%*s %f %f %f",
								&pGeomTemp->m_geoNodeTm.tmMat._21
								, &pGeomTemp->m_geoNodeTm.tmMat._23
								, &pGeomTemp->m_geoNodeTm.tmMat._22);
							pGeomTemp->m_geoNodeTm.tmMat._24 = 0.f;
						}
						else if (stTemp == "*TM_ROW1")
						{
							sscanf_s(szTemp, "%*s %f %f %f",
								&pGeomTemp->m_geoNodeTm.tmMat._31
								, &pGeomTemp->m_geoNodeTm.tmMat._33
								, &pGeomTemp->m_geoNodeTm.tmMat._32);
							pGeomTemp->m_geoNodeTm.tmMat._34 = 0.f;
						}
						else if (stTemp == "*TM_ROW3")
						{
							sscanf_s(szTemp, "%*s %f %f %f",
								&pGeomTemp->m_geoNodeTm.tmMat._41
								, &pGeomTemp->m_geoNodeTm.tmMat._43
								, &pGeomTemp->m_geoNodeTm.tmMat._42);
							pGeomTemp->m_geoNodeTm.tmMat._44 = 1.f;
						}
						else if (stTemp == "*TM_POS")
						{
							sscanf_s(szTemp, "%*s %f %f %f",
								&pGeomTemp->m_geoNodeTm.tmPos.x
								, &pGeomTemp->m_geoNodeTm.tmPos.z
								, &pGeomTemp->m_geoNodeTm.tmPos.y);
						}
						else if (stTemp == "*TM_ROTAXIS")
						{
							sscanf_s(szTemp, "%*s %f %f %f",
								&pGeomTemp->m_geoNodeTm.tmRotAxis.x
								, &pGeomTemp->m_geoNodeTm.tmRotAxis.z
								, &pGeomTemp->m_geoNodeTm.tmRotAxis.y);
						}
						else if (stTemp == "*TM_ROTANGLE")
						{
							sscanf_s(szTemp, "%*s %f",
								&pGeomTemp->m_geoNodeTm.tmRotAngle);
						}
						else if (stTemp == "*TM_SCALE")
						{
							sscanf_s(szTemp, "%*s %f %f %f",
								&pGeomTemp->m_geoNodeTm.tmScale.x
								, &pGeomTemp->m_geoNodeTm.tmScale.z
								, &pGeomTemp->m_geoNodeTm.tmScale.y);
						}
						else if (stTemp == "*TM_SCALEAXIS")
						{
							sscanf_s(szTemp, "%*s %f %f %f",
								&pGeomTemp->m_geoNodeTm.tmScaleAxis.x
								, &pGeomTemp->m_geoNodeTm.tmScaleAxis.z
								, &pGeomTemp->m_geoNodeTm.tmScaleAxis.y);
						}
						else if (stTemp == "*TM_SCALEAXISANG")
						{
							sscanf_s(szTemp, "%*s %f",
								&pGeomTemp->m_geoNodeTm.tmScaleAxisAng);
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
								pGeomTemp->m_geoMesh.vecVertex[i+1].p = vecV[z];
								pGeomTemp->m_geoMesh.vecVertex[i+2].p = vecV[y];
							}
							fgets(szTemp, 1024, fp);
						}
						else if (stTemp == "*MESH_NUMTVERTEX")
						{
							sscanf_s(szTemp, "%*s %d", 
								&pGeomTemp->m_geoMesh.NumTVertex);
							vecVT.resize(pGeomTemp->m_geoMesh.NumTVertex);
						}
						else if (stTemp == "*MESH_TVERTLIST")
						{
							for (int i = 0; i < vecVT.size(); i++)
							{
								fgets(szTemp, 1024, fp);
								std::string stTemp;
								sscanf_s(szTemp, "%*s %*d %f %f %*f", 
									&vecVT[i].x, &vecVT[i].y);
								vecVT[i].y = 1.f - vecVT[i].y;
							}
							fgets(szTemp, 1024, fp);
						}
						else if (stTemp == "*MESH_NUMTVFACES")
						{
							sscanf_s(szTemp, "%*s %d",
								&pGeomTemp->m_geoMesh.NumTFace);
						}
						else if (stTemp == "*MESH_TFACELIST")
						{
							for (int i = 0; i < pGeomTemp->m_geoMesh.NumTFace; i++)
							{
								fgets(szTemp, 1024, fp);
								std::string stTemp;
								int x, y, z;
								sscanf_s(szTemp, "%*s %*s %d %d %d", &x, &y, &z);
								pGeomTemp->m_geoMesh.vecVertex[i*3].t = vecVT[x];
								pGeomTemp->m_geoMesh.vecVertex[i*3 + 1].t = vecVT[z];
								pGeomTemp->m_geoMesh.vecVertex[i*3 + 2].t = vecVT[y];
							}
							fgets(szTemp, 1024, fp);
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
								int vertexIndex, indexCnt;
								
								if (stTemp == "}")
								{
									break;
								}
								else if (stTemp == "*MESH_FACENORMAL")
								{
									sscanf_s(szTemp, "%*s %d", &vertexIndex);
									indexCnt = 0;
								}
								else if (stTemp == "*MESH_VERTEXNORMAL")
								{
									sscanf_s(szTemp, "%*s %*d %f %f %f",
										&pGeomTemp->m_geoMesh.vecVertex[vertexIndex*3 + indexCnt].n.x
										, &pGeomTemp->m_geoMesh.vecVertex[vertexIndex * 3 + indexCnt].n.z
										, &pGeomTemp->m_geoMesh.vecVertex[vertexIndex * 3 + indexCnt].n.y);
									indexCnt++;
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
						else if (stTemp == "*CONTROL_ROT_TCB")
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
				else if (stTemp == "*MATERIAL_REF")
				{
					sscanf_s(szTemp, "%*s %d", &pGeomTemp->mtl_ref);
					pGeomTemp->mtl_ref++;
				}
				else if (stTemp == "*WIREFRAME_COLOR")
				{
					sscanf_s(szTemp, "%*s %f %f %f",
						&pGeomTemp->m_wireFrameColor.x,
						&pGeomTemp->m_wireFrameColor.y,
						&pGeomTemp->m_wireFrameColor.z);
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
