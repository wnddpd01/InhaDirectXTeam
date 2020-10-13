#include "stdafx.h"
#include "cAseLoader.h"
#include "cMtlTex.h"
#include "cGroup.h"
#include "cMtlTex.h"
#include "cCubeNode.h"

void cAseLoader::LoadMaterial(FILE* fp)
{
	if(!fp)
	{
		return;
	}
	char line[512];
	char materialName[32];
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
				fgets(line, sizeof(line), fp);
				return;
			}
		}
		char* key = strtok(line, "\t ");
		cout << key << endl;
		if(strcmp(key, "*MATERIAL_NAME") == 0)
		{
			key = strchr(&line[strlen(line) + 1], '\"');
			strcpy(materialName, &key[1]);
			key = strchr(materialName, '\"');
			*key = '\0';
			m_mapMtlTex[materialName] = new cMtlTex;
		}
		else if (strcmp(key, "*MATERIAL_AMBIENT") == 0)
		{
			D3DMATERIAL9 & material = m_mapMtlTex[materialName]->GetMaterial();
			key = strtok(NULL, "\t ");
			material.Ambient.r = stof(key);
			key = strtok(NULL, "\t ");
			material.Ambient.g = stof(key);
			key = strtok(NULL, "\t ");
			material.Ambient.b = stof(key);
		}
		else if (strcmp(key, "*MATERIAL_DIFFUSE") == 0)
		{
			D3DMATERIAL9& material = m_mapMtlTex[materialName]->GetMaterial();
			key = strtok(NULL, "\t ");
			material.Diffuse.r = stof(key);
			key = strtok(NULL, "\t ");
			material.Diffuse.g = stof(key);
			key = strtok(NULL, "\t ");
			material.Diffuse.b = stof(key);
		}
		else if (strcmp(key, "*MATERIAL_SPECULAR") == 0)
		{
			D3DMATERIAL9& material = m_mapMtlTex[materialName]->GetMaterial();
			key = strtok(NULL, "\t ");
			material.Specular.r = stof(key);
			key = strtok(NULL, "\t ");
			material.Specular.g = stof(key);
			key = strtok(NULL, "\t ");
			material.Specular.b = stof(key);
		}
		else if (strcmp(key, "*MATERIAL_TRANSPARENCY") == 0)
		{
			D3DMATERIAL9& material = m_mapMtlTex[materialName]->GetMaterial();
			key = strtok(NULL, "\t ");
			material.Specular.a = material.Diffuse.a = material.Ambient.a = stof(key);
		}
		else if (strcmp(key, "*MATERIAL_SHINE") == 0)
		{
			D3DMATERIAL9& material = m_mapMtlTex[materialName]->GetMaterial();
			key = strtok(NULL, "\t ");
			material.Power = stof(key);
		}
		else if (strcmp(key, "*MATERIAL_SELFILLUM") == 0)
		{
			D3DMATERIAL9& material = m_mapMtlTex[materialName]->GetMaterial();
			key = strtok(NULL, "\t ");
		}
		else if (strcmp(key, "*BITMAP") == 0)
		{
			char texturePath[32];
			key = strchr(&line[strlen(line) + 1], '\"');
			strcpy(texturePath, &key[1]);
			key = strchr(texturePath, '\"');
			*key = '\0';
			m_mapMtlTex[materialName]->SetTexture(g_pTextureManger->GetTexture(texturePath));
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
	size_t brace_count = 0;
	size_t num_vertex = 0;
	size_t num_faces = 0;

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
				fgets(line, sizeof(line), fp);
				return;
			}
		}
		char* key = strtok(line, "\t ");
		cout << key << endl;
		if (strcmp(key, "*NODE_NAME") == 0)
		{
			key = strchr(&line[strlen(line) + 1], '\"');
			strcpy(nodeName, &key[1]);
			key = strchr(nodeName, '\"');
			*key = '\0';
			if (m_mapCubeNode.find(nodeName) == m_mapCubeNode.end())
			{
				m_mapCubeNode[nodeName] = new cCubeNode;
			}
		}
		else if (strcmp(key, "*MATERIAL_AMBIENT") == 0)
		{
			D3DMATERIAL9& material = m_mapMtlTex[nodeName]->GetMaterial();
			key = strtok(NULL, "\t ");
			material.Ambient.r = stof(key);
			key = strtok(NULL, "\t ");
			material.Ambient.g = stof(key);
			key = strtok(NULL, "\t ");
			material.Ambient.b = stof(key);
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
			}
		}
		else if (strcmp(key, "*MESH_FACE_LIST") == 0)
		{
			for (int i = 0; i < num_vertex; ++i)
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
	}
}

void cAseLoader::Load(std::vector<cGroup*>& vecGroup, char* szFolder, char* szFile)
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
		cout << key << endl;
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
				fgets(line, sizeof(line), fp);
				key = strtok(line, "\t ");
				if(strcmp(key, "*MATERIAL") == 0)
				{
					LoadMaterial(fp);
				}
			}
		}
		else if(strcmp(key, "*GEOMOBJECT") == 0)
		{
			LoadGeomObject(fp);
		}
	}
	fclose(fp);
}
