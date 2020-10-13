#include "stdafx.h"
#include "CasteljouMove.h"
#include "cCubeMan.h"


CasteljouMove::CasteljouMove()
{
}


CasteljouMove::~CasteljouMove()
{
}

void CasteljouMove::AddCheckPoint(CheckPoint& point)
{
	m_vecCheckPoints.push_back(point);
}

void CasteljouMove::DeleteCheckPoint(int index)
{
	m_vecCheckPoints.erase(m_vecCheckPoints.begin() + index);
	
}

void CasteljouMove::ClearCheckPoint()
{
	m_vecCheckPoints.clear();
}

void CasteljouMove::MoveCubeMan(cCubeMan& target)
{
	/*
	int i = 0;
	while (i != m_vecMovePoints.size())
	{
		if (target.MoveTo(m_vecMovePoints[i]))
			i++;
	}


	*/
}

void CasteljouMove::CalculPath()
{
	float reso = 10.f;
	ST_PC_VERTEX ver;
	ver.c = D3DCOLOR_XRGB(255, 0, 255);
	
	for(int k = 0; k < m_vecCheckPoints.size(); k++)
	{
		for (int j = 0; j < reso; j++)
		{
			D3DXVECTOR3 result(0.f, 0.f, 0.f);
			int pathSize = m_vecCheckPoints[k].SplinePoint.size() -1;

			for (int i = 0; i < pathSize + 1; i++)
			{
				if (((j == 0) || (j == reso)) && (i != 0))
					continue;
				
				result.x += (biCoefficient(pathSize, i)
					* powf((1.f - (j / reso)), pathSize - i)
					* powf(j / reso, i)
					* m_vecCheckPoints[k].SplinePoint[i].x);


				result.z += (biCoefficient(pathSize, i)
					* powf((1.f - (j / reso)), pathSize - i)
					* powf(j / reso, i)
					* m_vecCheckPoints[k].SplinePoint[i].z);
			}
			
			m_vecMovePoints.push_back(result);
			ver.p = result;
			m_vecVertexPoints.push_back(ver);
		}

	}
}

void CasteljouMove::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, m_vecVertexPoints.size()-1, &m_vecVertexPoints[0],
		sizeof(ST_PC_VERTEX));
}

float CasteljouMove::biCoefficient(int top, int bot)
{
	if (bot == 0)
		return 1.f;
	
	float result = 1.f;
	for(int i = 0; i < bot; i++)
	{
		result *= top--;
	}

	return result / Facto(bot);
}

int CasteljouMove::Facto(int num)
{
	int result = num;
	while(num > 1)
	{
		num--;
		result *= num;
	}
	return result;
}
