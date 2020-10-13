#include "stdafx.h"
#include "ObjParser.h"




ObjParser::ObjParser()
{
}


ObjParser::~ObjParser()
{
}

void ObjParser::Setup(std::string fileName)
{
	std::vector<D3DXVECTOR3> FileVertex;
	std::vector<D3DXVECTOR2> FileTexture;
	std::vector<D3DXVECTOR3> FileNormal;
	D3DXVECTOR3 vec;
	D3DXVECTOR2 vec2;
	m_vecVertex.clear();
	std::string objName = "obj\\" + fileName;
	std::ifstream in(objName);
	std::string s;
	if (in.is_open()) {
		while (!in.eof())
		{
			in >> s;
			
			if (s == "v")
			{
				in >> s;
				vec.x = stof(s);
				in >> s;
				vec.y = stof(s);
				in >> s;
				vec.z = stof(s);
				FileVertex.push_back(vec);
			}
			else if (s == "vt")
			{
				in >> s;
				vec2.x = stof(s);
				in >> s;
				vec2.y = stof(s);
				in >> s;
				//vec.z = stof(s);
				FileTexture.push_back(vec2);
			}
			else if (s == "vn")
			{
				in >> s;
				vec.x = stof(s);
				in >> s;
				vec.y = stof(s);
				in >> s;
				vec.z = stof(s);
				FileNormal.push_back(vec);
			}
			else if (s == "f")
			{
				ST_PNT_VERTEX PNTtemp;
				
				in >> s;
				std::stringstream ssX(s);
				std::getline(ssX, s, '/');
				PNTtemp.p = FileVertex[stoi(s) - 1];
				std::getline(ssX, s, '/');
				PNTtemp.t = FileTexture[stoi(s) - 1];
				std::getline(ssX, s, ' ');
				PNTtemp.n = FileNormal[stoi(s) - 1];
				m_vecVertex.push_back(PNTtemp);

				in >> s;
				std::stringstream ssY(s);
				std::getline(ssY, s, '/');
				PNTtemp.p = FileVertex[stoi(s) - 1];
				std::getline(ssY, s, '/');
				PNTtemp.t = FileTexture[stoi(s) - 1];
				std::getline(ssY, s, ' ');
				PNTtemp.n = FileNormal[stoi(s) - 1];
				m_vecVertex.push_back(PNTtemp);
				
				in >> s;
				std::stringstream ssZ(s);
				std::getline(ssZ, s, '/');
				PNTtemp.p = FileVertex[stoi(s) - 1];
				std::getline(ssZ, s, '/');
				PNTtemp.t = FileTexture[stoi(s) - 1];
				std::getline(ssZ, s, ' ');
				PNTtemp.n = FileNormal[stoi(s) - 1];
				m_vecVertex.push_back(PNTtemp);
			}
			else if (s == "mtllib")
			{
				in >> s;
				m_strMtlName = "obj\\" + s.assign(s.begin()+2, s.end());
			}
		}	
	}
	else {
		std::cout << "파일을 찾을 수 없습니다!" << std::endl;
	}
	in.close();


	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	
	std::ifstream mtlIn(m_strMtlName);
	if (mtlIn.is_open())
	{
		while (!mtlIn.eof())
		{
			mtlIn >> s;

			if (s == "Ka")
			{
				D3DXCOLOR Amb;
				mtlIn >> s;
				Amb.r = stof(s);
				mtlIn >> s;
				Amb.g = stof(s);
				mtlIn >> s;
				Amb.b = stof(s);
				m_stMtl.Ambient = Amb;
			}
			else if (s == "Kd")
			{
				D3DXCOLOR dif;
				mtlIn >> s;
				dif.r = stof(s);
				mtlIn >> s;
				dif.g = stof(s);
				mtlIn >> s;
				dif.b = stof(s);
				m_stMtl.Diffuse = dif;
			}
			else if (s == "Ks")
			{
				D3DXCOLOR spec;
				mtlIn >> s;
				spec.r = stof(s);
				mtlIn >> s;
				spec.g = stof(s);
				mtlIn >> s;
				spec.b = stof(s);
				m_stMtl.Specular = spec;
			}
			else if (s== "d")
			{
				mtlIn >> s;
				m_stMtl.Ambient.a = stof(s);
				m_stMtl.Diffuse.a = stof(s);
				m_stMtl.Specular.a = stof(s);
			}
			else if (s == "map_Kd")
			{
				mtlIn >> s;
				s = "obj\\" + s;
				m_wstrTextureName.assign(s.begin(), s.end());
			}
		}
	}
	D3DXCreateTextureFromFile(g_pD3DDevice, m_wstrTextureName.c_str(), &m_pTexture);
}

void ObjParser::Render()
{
	if (g_pD3DDevice)
	{
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		g_pD3DDevice->SetMaterial(&m_stMtl);
		g_pD3DDevice->SetTexture(0, m_pTexture);
		g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			m_vecVertex.size() / 3,
			&m_vecVertex[0],
			sizeof(ST_PNT_VERTEX));
		g_pD3DDevice->SetTexture(0, nullptr);
	}
}

void ObjParser::Update()
{
	
}
