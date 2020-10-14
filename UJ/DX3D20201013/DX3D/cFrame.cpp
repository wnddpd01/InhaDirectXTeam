#include "stdafx.h"
#include "cFrame.h"


cFrame::cFrame()
	:m_pMtlTex(NULL)
{
	D3DXMatrixIdentity(&m_matLocalTM);
	D3DXMatrixIdentity(&m_matWorldTM);
}


cFrame::~cFrame()
{
	SafeRelease(m_pMtlTex);
}

void cFrame::Update(int nKeyFrame, D3DXMATRIXA16* pMatParent)
{
	m_matWorldTM = m_matLocalTM;
	if(pMatParent)
	{
		m_matWorldTM *= *pMatParent;
	}
	for (auto m_vec_child : m_vecChild)
	{
		m_vec_child->Update(nKeyFrame, &m_matWorldTM);
	}
}

void cFrame::Render()
{
	if(m_pMtlTex)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
		g_pD3DDevice->SetTexture(0, m_pMtlTex->GetTexture());
		g_pD3DDevice->SetMaterial(&m_pMtlTex->GetMaterial());

		g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PNT_VERTEX));

	}
	for (auto child : m_vecChild)
	{
		child->Render();
	}
}

void cFrame::AddChild(cFrame* pChild)
{
	m_vecChild.push_back(pChild);
	
}

void cFrame::Destroy()
{
	for (auto child : m_vecChild)
	{
		child->Destroy();
	}
	this->Release();
}

void cFrame::CaclOriginLocalTM(D3DXMATRIXA16* pMatParent)
{
	// : WTM = LTM * pWTM;
	// : LTM = WTM * InvpWTM;
	m_matLocalTM = m_matWorldTM;
	if(pMatParent)
	{
		D3DXMATRIXA16 matInvParent;
		D3DXMatrixInverse(&matInvParent, NULL, pMatParent);
		m_matLocalTM = m_matWorldTM * matInvParent;
	}
	for (auto child : m_vecChild)
	{
		child->CaclOriginLocalTM(&m_matWorldTM);
	}
}
