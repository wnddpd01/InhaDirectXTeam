#include "stdafx.h"
#include "cAseLoader.h"
#include "cMtlTex.h"
#include "cGroup.h"
#include "cMtlTex.h"
#include "cCubeNode.h"
#include "cCubeMan.h"

void cAseLoader::LoadMaterial(FILE* fp)
{
	if(!fp)
	{
		return;
	}
	char line[512];
	char materialName[32];
	size_t materialRef = 0;
	size_t brace_count = 0;
	while (fgets(line, sizeof(line), fp) != NULL)
	{
		if(strchr(line, '{') != NULL)
		{
			brace_count++;
		}
		else if (strchr(line, '}') != NULL)
		{
			brace_count--;
			if (brace_count == 0)
			{
				return;
			}
		}
		char* key = strtok(line, "\t ");
		if (strcmp(key, "*MATERIAL") == 0)
		{
			key = strtok(NULL, "\t ");
			materialRef = stoi(key);
			m_mapMtlTex[materialRef] = new cMtlTex;
		}
		else if(strcmp(key, "*MATERIAL_NAME") == 0)
		{
			key = strchr(&line[strlen(line) + 1], '\"');
			strcpy(materialName, &key[1]);
			key = strchr(materialName, '\"');
			*key = '\0';
			//m_mapMtlTex[materialName] = new cMtlTex;
		}
		else if (strcmp(key, "*MATERIAL_AMBIENT") == 0)
		{
			D3DMATERIAL9 & material = m_mapMtlTex[materialRef]->GetMaterial();
			key = strtok(NULL, "\t ");
			material.Ambient.r = stof(key);
			key = strtok(NULL, "\t ");
			material.Ambient.g = stof(key);
			key = strtok(NULL, "\t ");
			material.Ambient.b = stof(key);
		}
		else if (strcmp(key, "*MATERIAL_DIFFUSE") == 0)
		{
			D3DMATERIAL9& material = m_mapMtlTex[materialRef]->GetMaterial();
			key = strtok(NULL, "\t ");
			material.Diffuse.r = stof(key);
			key = strtok(NULL, "\t ");
			material.Diffuse.g = stof(key);
			key = strtok(NULL, "\t ");
			material.Diffuse.b = stof(key);
		}
		else if (strcmp(key, "*MATERIAL_SPECULAR") == 0)
		{
			D3DMATERIAL9& material = m_mapMtlTex[materialRef]->GetMaterial();
			key = strtok(NULL, "\t ");
			material.Specular.r = stof(key);
			key = strtok(NULL, "\t ");
			material.Specular.g = stof(key);
			key = strtok(NULL, "\t ");
			material.Specular.b = stof(key);
		}
		else if (strcmp(key, "*MATERIAL_TRANSPARENCY") == 0)
		{
			D3DMATERIAL9& material = m_mapMtlTex[materialRef]->GetMaterial();
			key = strtok(NULL, "\t ");
			material.Specular.a = material.Diffuse.a = material.Ambient.a = stof(key);
		}
		else if (strcmp(key, "*MATERIAL_SHINE") == 0)
		{
			D3DMATERIAL9& material = m_mapMtlTex[materialRef]->GetMaterial();
			key = strtok(NULL, "\t ");
			material.Power = stof(key);
		}
		else if (strcmp(key, "*MATERIAL_SELFILLUM") == 0)
		{
			D3DMATERIAL9& material = m_mapMtlTex[materialRef]->GetMaterial();
			key = strtok(NULL, "\t ");
		}
		else if (strcmp(key, "*BITMAP") == 0)
		{
			char texturePath[32];
			key = strchr(&line[strlen(line) + 1], '\"');
			strcpy(texturePath, &key[1]);
			key = strchr(texturePath, '\"');
			*key = '\0';
			m_mapMtlTex[materialRef]->SetTexture(g_pTextureManger->GetTexture(texturePath));
		}
	}
}

void cAseLoader::LoadGeomObject(FILE* fp)
{
	if (!fp)
	{
		return;
	}
	char line[512];
	char nodeName[32];
	size_t brace_count = 1;
	size_t num_vertex = 0;
	size_t num_faces = 0;
	size_t num_tVertex = 0;
	size_t num_tFaces = 0;
	
	vector<D3DXVECTOR3> vertices;
	vector<D3DXVECTOR2> tex_vertices;
	vector<D3DXVECTOR3> normals;
	vector<ST_PNT_VERTEX> vecVertex;
	while (fgets(line, sizeof(line), fp) != NULL)
	{
		if (strchr(line, '{') != NULL)
		{
			brace_count++;
		}
		else if (strchr(line, '}') != NULL)
		{
			brace_count--;
			if (brace_count == 0)
			{
				m_mapCubeNode[nodeName]->m_vecVertex = vecVertex;
				return;
			}
		}
		char* key = strtok(line, "\t ");
		if (strcmp(key, "*NODE_NAME") == 0)
		{
			key = strchr(&line[strlen(line) + 1], '\"');
			strcpy(nodeName, &key[1]);
			key = strchr(nodeName, '\"');
			*key = '\0';
			if (m_mapCubeNode.find(nodeName) == m_mapCubeNode.end())
			{
				if(m_mapCubeNode.size() == 0)
				{
					rootNodeName = string(nodeName);
				}
				m_mapCubeNode[nodeName] = new cCubeNode;
			}
			if(strcmp(nodeName, "ponytail") == 0)
			{
				int a = 0;
			}
		}
		else if (strcmp(key, "*NODE_PARENT") == 0)
		{
			char parentName[32];
			key = strchr(&line[strlen(line) + 1], '\"');
			strcpy(parentName, &key[1]);
			key = strchr(parentName, '\"');
			*key = '\0';
			if (m_mapCubeNode.find(parentName) == m_mapCubeNode.end())
			{
				cout << "Parent Find Error" << endl;
				return;
			}
			m_mapCubeNode[parentName]->AddChild(m_mapCubeNode[nodeName]);
		}
		else if(strcmp(key, "*TM_ROW0") == 0)
		{
			key = strtok(NULL, "\t ");
			m_mapCubeNode[nodeName]->m_matLocalTM.m[0][0] = stof(key);
			key = strtok(NULL, "\t ");
			m_mapCubeNode[nodeName]->m_matLocalTM.m[0][2] = stof(key);
			key = strtok(NULL, "\t ");
			m_mapCubeNode[nodeName]->m_matLocalTM.m[0][1] = stof(key);
			m_mapCubeNode[nodeName]->m_matLocalTM.m[0][3] = 0;
		}
		else if (strcmp(key, "*TM_ROW1") == 0)
		{
			key = strtok(NULL, "\t ");
			m_mapCubeNode[nodeName]->m_matLocalTM.m[2][0] = stof(key);
			key = strtok(NULL, "\t ");
			m_mapCubeNode[nodeName]->m_matLocalTM.m[2][2] = stof(key);
			key = strtok(NULL, "\t ");
			m_mapCubeNode[nodeName]->m_matLocalTM.m[2][1] = stof(key);
			m_mapCubeNode[nodeName]->m_matLocalTM.m[2][3] = 0;
		}
		else if (strcmp(key, "*TM_ROW2") == 0)
		{
			key = strtok(NULL, "\t ");
			m_mapCubeNode[nodeName]->m_matLocalTM.m[1][0] = stof(key);
			key = strtok(NULL, "\t ");
			m_mapCubeNode[nodeName]->m_matLocalTM.m[1][2] = stof(key);
			key = strtok(NULL, "\t ");
			m_mapCubeNode[nodeName]->m_matLocalTM.m[1][1] = stof(key);
			m_mapCubeNode[nodeName]->m_matLocalTM.m[1][3] = 0;
		}
		else if (strcmp(key, "*TM_ROW3") == 0)
		{
			key = strtok(NULL, "\t ");
			m_mapCubeNode[nodeName]->m_matLocalTM.m[3][0] = stof(key);
			key = strtok(NULL, "\t ");
			m_mapCubeNode[nodeName]->m_matLocalTM.m[3][2] = stof(key);
			key = strtok(NULL, "\t ");
			m_mapCubeNode[nodeName]->m_matLocalTM.m[3][1] = stof(key);
			m_mapCubeNode[nodeName]->m_matLocalTM.m[3][3] = 1;

			if(m_mapCubeNode[nodeName]->GetParentWorldTM() != NULL)
			{
				D3DXMATRIXA16 parentMatInv;
				D3DXMatrixInverse(&parentMatInv, NULL, m_mapCubeNode[nodeName]->GetParentWorldTM());
				m_mapCubeNode[nodeName]->m_matLocalTM = m_mapCubeNode[nodeName]->m_matLocalTM * parentMatInv;
			}
		}
		else if (strcmp(key, "*MESH_NUMVERTEX") == 0)
		{
			key = strtok(NULL, "\t ");
			num_vertex = stoi(key);
		}
		else if (strcmp(key, "*MESH_NUMFACES") == 0)
		{
			key = strtok(NULL, "\t ");
			num_faces = stoi(key);
		}
		else if (strcmp(key, "*MESH_VERTEX_LIST") == 0)
		{
			for (int i = 0; i < num_vertex; ++i)
			{
				D3DXVECTOR3 vertex;
				fgets(line, sizeof(line), fp);
				key = strtok(line, "\t ");
				key = strtok(NULL, "\t ");
				vertex.x = stof(strtok(NULL, "\t "));
				vertex.z = stof(strtok(NULL, "\t "));
				vertex.y = stof(strtok(NULL, "\t "));
				vertices.push_back(vertex);
			}
		}
		else if (strcmp(key, "*MESH_FACE_LIST") == 0)
		{
			for (int i = 0; i < num_faces; ++i)
			{
				ST_PNT_VERTEX st_pnt_vertex;
				size_t a;
				size_t b;
				size_t c;
				fgets(line, sizeof(line), fp);
				strtok(line, "\t ");
				strtok(NULL, "\t ");
				strtok(NULL, "\t ");
				a = stoi(strtok(NULL, "\t "));
				strtok(NULL, "\t ");
				b = stoi(strtok(NULL, "\t "));
				strtok(NULL, "\t ");
				c = stoi(strtok(NULL, "\t "));
				st_pnt_vertex.p = vertices[a];
				vecVertex.push_back(st_pnt_vertex);
				st_pnt_vertex.p = vertices[c];
				vecVertex.push_back(st_pnt_vertex);
				st_pnt_vertex.p = vertices[b];
				vecVertex.push_back(st_pnt_vertex);
			}
		}
		else if (strcmp(key, "*MESH_NUMTVERTEX") == 0)
		{
			key = strtok(NULL, "\t ");
			num_tVertex = stoi(key);
		}
		else if (strcmp(key, "*MESH_TVERTLIST") == 0)
		{
			for (int i = 0; i < num_tVertex; ++i)
			{
				D3DXVECTOR2 vec_uv_tec;
				fgets(line, sizeof(line), fp);
				key = strtok(line, "\t ");
				key = strtok(NULL, "\t ");
				vec_uv_tec.x = stof(strtok(NULL, "\t "));
				vec_uv_tec.y = 1.0f - stof(strtok(NULL, "\t "));
				tex_vertices.push_back(vec_uv_tec);
			}
		}
		else if (strcmp(key, "*MESH_NUMTVFACES") == 0)
		{
			key = strtok(NULL, "\t ");
			num_tFaces = stoi(key);
		}
		else if (strcmp(key, "*MESH_TFACELIST") == 0)
		{
			for (int i = 0; i < num_tFaces; ++i)
			{
				size_t a;
				size_t b;
				size_t c;
				fgets(line, sizeof(line), fp);
				strtok(line, "\t ");
				strtok(NULL, "\t ");
				a = stoi(strtok(NULL, "\t "));
				b = stoi(strtok(NULL, "\t "));
				c = stoi(strtok(NULL, "\t "));
				vecVertex[i * 3].t = tex_vertices[a];
				vecVertex[i * 3 + 1].t = tex_vertices[c];
				vecVertex[i * 3 + 2].t = tex_vertices[b];
			}
		}
		else if (strcmp(key, "*MESH_NORMALS") == 0)
		{
			for (int i = 0; i < num_faces; ++i)
			{
				D3DXVECTOR3 normal[3];
				fgets(line, sizeof(line), fp);
				for (int j = 0; j < 3; ++j)
				{
					fgets(line, sizeof(line), fp);
					strtok(line, "\t ");
					strtok(NULL, "\t ");
					normal[j].x = stof(strtok(NULL, "\t "));
					normal[j].z = stof(strtok(NULL, "\t "));
					normal[j].y = stof(strtok(NULL, "\t "));
				}
				vecVertex[i * 3].n = normal[0];
				vecVertex[i * 3 + 1].n = normal[2];
				vecVertex[i * 3 + 2].n = normal[1];
			}
		}
		else if (strcmp(key, "*MATERIAL_REF") == 0)
		{
			size_t materialRef  = stoi(strtok(NULL, "\t "));
			m_mapCubeNode[nodeName]->m_pMtlTex = m_mapMtlTex[materialRef];
		}
	}
}

void cAseLoader::Load(cCubeNode ** root_node, char* szFolder, char* szFile)
{
	string fileDir = string(szFolder) + string("/") + string(szFile);
	FILE* fp = fopen(fileDir.c_str(), "r");
	
	if (!fp)
	{
		return;
	}
	char line[512];
	char materialName[32];
	while (fgets(line, sizeof(line), fp) != NULL)
	{
		char* key = strtok(line, "\t ");
		if(strcmp(key,"*MATERIAL_LIST") == 0)
		{
			fgets(line, sizeof(line), fp);
			key = strtok(line, "\t ");
			size_t material_count = 0;
			if(strcmp(key, "*MATERIAL_COUNT") == 0)
			{
				material_count = stoi(strtok(NULL, " "));
			}
			for (size_t i = 0; i < material_count; i++)
			{
				LoadMaterial(fp);
			}
		}
		else if(strcmp(key, "*GEOMOBJECT") == 0)
		{
			LoadGeomObject(fp);
		}
	}
	fclose(fp);
	/*for (auto it : m_mapMtlTex)
	{
		SafeRelease(it.second);
	}*/
	//m_mapMtlTex.clear();
	*root_node = m_mapCubeNode[rootNodeName.c_str()];
	cout << m_mapCubeNode.size() << endl;
	m_mapCubeNode.clear();
}
