#include "stdafx.h"
#include "cHexagon.h"
#include "cPyramid.h"

void cHexagon::SetBezier(int num, size_t t_, vector<ST_PC_VERTEX>& vertex)
{
	if (num > vertex.size())
		num = vertex.size();
	ST_PC_VERTEX pc_vertex;
	pc_vertex.c = RGB(255, 0 , 0);
	pc_vertex.p = vertex[0].p;

	for (int t = 0; t < t_; ++t)
	{
		float time = float(t) / t_;
		D3DXVECTOR3 result = { 0, 0, 0 };
		for (int i = 0; i < num; ++i)
		{
			float cof = binomial_coefficient(num - 1, i) * pow(1.0f - time, num - 1 - i) * pow(time, i);
			result.x += cof * vertex[i].p.x;
			result.z += cof * vertex[i].p.z;
		}
		pc_vertex.p = result;
		st_pc_bezier_vertices_.push_back(pc_vertex);
	}
	pc_vertex.p = vertex[num - 1].p;
	st_pc_bezier_vertices_.push_back(pc_vertex);
}

cHexagon::cHexagon()
{
}


cHexagon::~cHexagon()
{
}

void cHexagon::Setup()
{
	cPyramid * pPyramid;
	ST_PC_VERTEX st_pc_vertex;
	st_pc_vertex.c = RGB(0, 255, 0);
	D3DXMATRIXA16 matR;
	D3DXVECTOR3 hexaPos = D3DXVECTOR3(10, 0, 0);
	float rotY = 0;
	for (int i = 0; i < 6; i++)
	{
		D3DXMATRIXA16 matRotY;
		D3DXVECTOR3 newHexaPos;
		pPyramid = new cPyramid;
		D3DXMatrixRotationZ(&matR, D3DX_PI);
		pPyramid->Setup(D3DCOLOR_XRGB(0, 255, 0), matR);
		D3DXMatrixRotationY(&matRotY, rotY);
		D3DXVec3TransformNormal(&newHexaPos, &hexaPos, &matRotY);
		pPyramid->SetPosition(newHexaPos);
		pyramids_.push_back(pPyramid);
		st_pc_vertex.p = newHexaPos;
		this->st_pc_vertices_.push_back(st_pc_vertex);
		rotY += D3DX_PI / 3.0f;
	}
	this->st_pc_vertices_.push_back(st_pc_vertices_[0]);
	SetBezier(7, 10, st_pc_vertices_);
}

void cHexagon::Render()
{
	for (auto pyramid : pyramids_)
	{
		pyramid->Render();
	}g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, st_pc_vertices_.size() - 1, &st_pc_vertices_[0], sizeof(ST_PC_VERTEX));
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, st_pc_bezier_vertices_.size() - 1, &st_pc_bezier_vertices_[0], sizeof(ST_PC_VERTEX));
}
