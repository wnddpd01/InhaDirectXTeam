#include "stdafx.h"
#include "cCube.h"


cCube::cCube()
	:m_pVertexBuff(NULL)
	,m_pIndexBuff(NULL)
{	 
}


cCube::~cCube()
{
	SAFE_RELEASE(m_pVertexBuff);
	SAFE_RELEASE(m_pIndexBuff);
}

void cCube::Setup(D3DXMATRIXA16* pMat, vector<D3DXVECTOR2>* vecTVertex /*= NULL*/)
{
	g_pD3DDevice->CreateVertexBuffer(8 * sizeof(ST_PNT_VERTEX), D3DUSAGE_WRITEONLY, ST_PNT_VERTEX::FVF, D3DPOOL_MANAGED, &m_pVertexBuff, 0);
	g_pD3DDevice->CreateIndexBuffer(36 * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIndexBuff, 0);

	ST_PNT_VERTEX stV = ST_PNT_VERTEX(D3DXVECTOR3 (0,0,0), D3DXVECTOR3(1,1,1), D3DXVECTOR2(0,0));

	ST_PNT_VERTEX* vecVertex;
	m_pVertexBuff->Lock(0, 0, (void**)&vecVertex, 0);

	stV.p = D3DXVECTOR3(-1.0f, -1.0f, -1.0f); 
	vecVertex[0] = stV;
	stV.p = (D3DXVECTOR3(-1.0f, 1.0f, -1.0f));
	vecVertex[1]=  stV; 
	stV.p = (D3DXVECTOR3(1.0f, 1.0f, -1.0f));
	vecVertex[2]=  stV; 
	stV.p = (D3DXVECTOR3(1.0f, -1.0f, -1.0f));
	vecVertex[3]=  stV; 
	stV.p = (D3DXVECTOR3(-1.0f, -1.0f, 1.0f));
	vecVertex[4]=  stV; 
	stV.p = (D3DXVECTOR3(-1.0f, 1.0f, 1.0f));
	vecVertex[5]=  stV; 
	stV.p = (D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	vecVertex[6]=  stV; 
	stV.p = (D3DXVECTOR3(1.0f, -1.0f, 1.0f));
	vecVertex[7]=  stV; 

	m_pVertexBuff->Unlock();

	WORD* pIndice = 0;
	m_pIndexBuff->Lock(0, 0, (void**)&pIndice, 0);
	pIndice[0] = 0;
	pIndice[1] = 1;
	pIndice[2] = 2;
	pIndice[3] = 0;
	pIndice[4] = 2;
	pIndice[5] = 3;

	pIndice[6] = 4;
	pIndice[7] = 6;
	pIndice[8] = 5;
	pIndice[9] = 4;
	pIndice[10] = 7;
	pIndice[11] = 6;

	pIndice[12] = 0;
	pIndice[13] = 4;
	pIndice[14] = 1;
	pIndice[15] = 1;
	pIndice[16] = 4;
	pIndice[17] = 5;

	pIndice[18] = 2;
	pIndice[19] = 6;
	pIndice[20] = 3;
	pIndice[21] = 3;
	pIndice[22] = 6;
	pIndice[23] = 7;

	pIndice[24] = 0;
	pIndice[25] = 3;
	pIndice[26] = 4;
	pIndice[27] = 3;
	pIndice[28] = 7;
	pIndice[29] = 4;

	pIndice[30] = 1;
	pIndice[31] = 5;
	pIndice[32] = 2;
	pIndice[33] = 2;
	pIndice[34] = 5;
	pIndice[35] = 6;

	m_pIndexBuff->Unlock();

	/*D3DXMATRIXA16 matWorld;

	if (pMat)
		matWorld = *pMat;
	else
		D3DXMatrixIdentity(&matWorld);

	for (int i = 0; i < vecVertex.size(); ++i)
		D3DXVec3TransformCoord(&vecVertex[i], &vecVertex[i], &matWorld);

	D3DXVECTOR3 vNormal;

	if (vecTVertex != NULL)
	{
		ComputeNormal(&vNormal, &vecVertex[0], &vecVertex[1], &vecVertex[2]);
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[0], vNormal, (*vecTVertex)[0]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[1], vNormal, (*vecTVertex)[1]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[2], vNormal, (*vecTVertex)[2]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[0], vNormal, (*vecTVertex)[3]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[2], vNormal, (*vecTVertex)[4]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[3], vNormal, (*vecTVertex)[5]));
		ComputeNormal(&vNormal, &vecVertex[4], &vecVertex[6], &vecVertex[5]);
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[4], vNormal, (*vecTVertex)[6]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[6], vNormal, (*vecTVertex)[7]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[5], vNormal, (*vecTVertex)[8]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[4], vNormal, (*vecTVertex)[9]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[7], vNormal, (*vecTVertex)[10]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[6], vNormal, (*vecTVertex)[11]));
		ComputeNormal(&vNormal, &vecVertex[0], &vecVertex[4], &vecVertex[1]);
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[0], vNormal, (*vecTVertex)[12]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[4], vNormal, (*vecTVertex)[13]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[1], vNormal, (*vecTVertex)[14]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[1], vNormal, (*vecTVertex)[15]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[4], vNormal, (*vecTVertex)[16]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[5], vNormal, (*vecTVertex)[17]));
		ComputeNormal(&vNormal, &vecVertex[2], &vecVertex[6], &vecVertex[3]);
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[2], vNormal, (*vecTVertex)[18]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[6], vNormal, (*vecTVertex)[19]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[3], vNormal, (*vecTVertex)[20]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[3], vNormal, (*vecTVertex)[21]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[6], vNormal, (*vecTVertex)[22]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[7], vNormal, (*vecTVertex)[23]));
		ComputeNormal(&vNormal, &vecVertex[0], &vecVertex[3], &vecVertex[4]);
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[0], vNormal, (*vecTVertex)[24]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[3], vNormal, (*vecTVertex)[25]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[4], vNormal, (*vecTVertex)[26]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[3], vNormal, (*vecTVertex)[27]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[7], vNormal, (*vecTVertex)[28]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[4], vNormal, (*vecTVertex)[29]));
		ComputeNormal(&vNormal, &vecVertex[1], &vecVertex[5], &vecVertex[2]);
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[1], vNormal, (*vecTVertex)[30]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[5], vNormal, (*vecTVertex)[31]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[2], vNormal, (*vecTVertex)[32]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[2], vNormal, (*vecTVertex)[33]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[5], vNormal, (*vecTVertex)[34]));
		m_vecPNTVertex.push_back(ST_PNT_VERTEX(vecVertex[6], vNormal, (*vecTVertex)[35]));
	}
	else
	{
		ComputeNormal(&vNormal, &vecVertex[0], &vecVertex[1], &vecVertex[2]);
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[0], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[1], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[2], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[0], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[2], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[3], vNormal));
		ComputeNormal(&vNormal, &vecVertex[4], &vecVertex[6], &vecVertex[5]);
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[4], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[6], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[5], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[4], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[7], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[6], vNormal));
		ComputeNormal(&vNormal, &vecVertex[0], &vecVertex[4], &vecVertex[1]);
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[0], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[4], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[1], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[1], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[4], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[5], vNormal));
		ComputeNormal(&vNormal, &vecVertex[2], &vecVertex[6], &vecVertex[3]);
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[2], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[6], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[3], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[3], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[6], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[7], vNormal));
		ComputeNormal(&vNormal, &vecVertex[0], &vecVertex[3], &vecVertex[4]);
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[0], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[3], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[4], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[3], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[7], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[4], vNormal));
		ComputeNormal(&vNormal, &vecVertex[1], &vecVertex[5], &vecVertex[2]);
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[1], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[5], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[2], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[2], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[5], vNormal));
		m_vecPNVertex.push_back(ST_PN_VERTEX(vecVertex[6], vNormal));
	}*/
}

void cCube::Update(D3DXMATRIXA16* pParentWorldTM)
{
	cGameObject::Update(pParentWorldTM);

	for each (auto p in m_vecChild)
	{
		p->SetAnimation(m_bAnimation);
		p->Update(&m_matWorld);
	}
}

void cCube::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	//if (!m_vecPNTVertex.empty())
	//{
	g_pD3DDevice->SetStreamSource(0, m_pVertexBuff, 0, sizeof(ST_PNT_VERTEX));
	g_pD3DDevice->SetIndices(m_pIndexBuff);
	//	g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("super"));
	//	g_pD3DDevice->SetMaterial(&WHITE_MTRL);
		g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
		g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0,0,8,0,12);
	//}
	//else if (!m_vecPNVertex.empty())
	//{
	//	g_pD3DDevice->SetTexture(0, NULL);
	//	g_pD3DDevice->SetMaterial(&WHITE_MTRL);
	//	g_pD3DDevice->SetFVF(ST_PN_VERTEX::FVF);
	//	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecPNVertex.size() / 3,
	//		&m_vecPNVertex[0], sizeof(ST_PN_VERTEX));
	//}

	//for each (auto p in m_vecChild)
	//{
	//	p->Render();
	//}
}

void cCube::AddChild(cCube* pChild)
{
	m_vecChild.push_back(pChild);
}