#include "stdafx.h"
#include "Group.h"

Group::Group()
	: m_pMtlTex(nullptr)
{
}

Group::~Group()
{
	SAFE_RELEASE(m_pMtlTex);
}

void Group::Render()
{
	if (m_pMtlTex)
	{
		gD3Device->SetTexture(0, m_pMtlTex->GetTexture());
		gD3Device->SetMaterial(&m_pMtlTex->GetMaterial());
	}

	gD3Device->SetFVF(Vertex::FVF);
	gD3Device->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0],
		sizeof(Vertex));
}
