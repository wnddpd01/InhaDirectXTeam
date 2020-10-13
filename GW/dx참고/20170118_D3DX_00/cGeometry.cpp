#include "stdafx.h"
#include "cGeometry.h"


cGeometry::cGeometry()
	: m_pMtrlTex(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matLocal);
}


cGeometry::~cGeometry()
{
}

void cGeometry::Render()
{
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	
	for (int i = 0; i < m_vecChild.size(); i++)
	{
		m_vecChild[i]->Render();
	}

	if (m_pMtrlTex == NULL)
		return;
	else
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
		g_pD3DDevice->SetTexture(0, m_pMtrlTex->GetTexture());
		g_pD3DDevice->SetMaterial(&m_pMtrlTex->GetMtrl());
		g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3,
			&m_vecVertex[0], sizeof(ST_PNT_VERTEX));
	}
}

cGeometry * cGeometry::GetMyParents(string _sParentsName)
{
	if (!strcmp(m_sMyName.c_str(), _sParentsName.c_str()))
		return this;

	cGeometry * pParents = NULL;
	for (int i = 0; i < m_vecChild.size(); i++)
	{
		pParents = m_vecChild[i]->GetMyParents(_sParentsName);
		if (pParents != NULL)
			return pParents;
	}

	return NULL;
}

bool cGeometry::AddMyChild(cGeometry * _pChild)
{
	if (_pChild == NULL)
		return false;

	m_vecChild.push_back(_pChild);

	return true;
}

void cGeometry::SetMyName(char * _pName)
{
	m_sMyName = _pName;
}

void cGeometry::CalcLocalTM(cGeometry * pParent)
{
	m_matLocal = m_matWorld;

	if (pParent)
	{
		D3DXMATRIXA16 matInverse;
		D3DXMatrixInverse(&matInverse, 0, &pParent->m_matWorld);
		m_matLocal *= matInverse;
	}

	for (int i = 0; i < m_vecChild.size(); i++)
	{
		m_vecChild[i]->CalcLocalTM(this);
	}

}

void cGeometry::CalcLocalTranslationMatrix(IN int _nKeyFrame, OUT D3DXMATRIXA16 & _mat)
{
	// 벡터의 프론트와 백을 써서 제일 작은것보다 작은 경우 작은걸로 적용, 큰 경우 큰 걸로 적용
	// D3DXVec3Lerp() 사용해서 보간
	D3DXMatrixIdentity(&_mat);

	if (m_vecPosTrack.empty())
	{
		_mat._41 = m_matLocal._41;
		_mat._42 = m_matLocal._42;
		_mat._43 = m_matLocal._43;
	}
	else if (_nKeyFrame <= m_vecPosTrack.front().n)
	{
		_mat._41 = m_vecPosTrack.front().v.x;
		_mat._42 = m_vecPosTrack.front().v.y;
		_mat._43 = m_vecPosTrack.front().v.z;
	}
	else if (_nKeyFrame >= m_vecPosTrack.back().n)
	{
		_mat._41 = m_vecPosTrack.back().v.x;
		_mat._42 = m_vecPosTrack.back().v.y;
		_mat._43 = m_vecPosTrack.back().v.z;
	}
	else
	{
		for (int i = 0; i < m_vecPosTrack.size()-1; ++i)
		{
			if (_nKeyFrame >= m_vecPosTrack[i].n && _nKeyFrame < m_vecPosTrack[i+1].n)
			{
				D3DXVECTOR3 vPos;
				D3DXVec3Lerp(&vPos, &m_vecPosTrack[i].v, &m_vecPosTrack[i+1].v, (float)(_nKeyFrame - m_vecPosTrack[i].n) / (float)(m_vecPosTrack[i + 1].n - m_vecPosTrack[i].n));
				_mat._41 = vPos.x;
				_mat._42 = vPos.y;
				_mat._43 = vPos.z;

				break;
			}
		}
	}

}

void cGeometry::CalcLocalRotationMatrix(IN int _nKeyFrame, OUT D3DXMATRIXA16 & _mat)
{
	// 구면보간 : D3DXQuaternionSlerp()
	// 로테이션 매트릭스 입력 : D3DxMatrixrotationQuaternion()
	//_mat = m_matLocal;

	//D3DXMatrixIdentity(&_mat);
	_mat = m_matLocal;

	if (m_vecRotTrack.empty())
	{
		_mat = m_matLocal;
		_mat._41 = 0.0f;
		_mat._42 = 0.0f;
		_mat._43 = 0.0f;
	}
	else if (_nKeyFrame <= m_vecRotTrack.front().n)
	{
		D3DXMatrixRotationQuaternion(&_mat, &m_vecRotTrack.front().q);
	
	}
	else if (_nKeyFrame >= m_vecRotTrack.back().n)
	{
		D3DXMatrixRotationQuaternion(&_mat, &m_vecRotTrack.back().q);

	}
	else
	{
			for (int i = 0; i < m_vecRotTrack.size() - 1; ++i)
			{
				if (_nKeyFrame >= m_vecRotTrack[i].n && _nKeyFrame < m_vecRotTrack[i + 1].n)
				{
					D3DXQUATERNION qRot;
					D3DXQuaternionSlerp(&qRot, &m_vecRotTrack[i].q, &m_vecRotTrack[i+1].q, (float)(_nKeyFrame- m_vecRotTrack[i].n) / (float)(m_vecRotTrack[i + 1].n - m_vecRotTrack[i].n));
					D3DXMatrixRotationQuaternion(&_mat, &qRot);
					break;
				}
		}
	}
}

void cGeometry::Update(int _nKeyFrame, D3DXMATRIXA16 * _pParentsMat)
{
	
	//TM매트리스의 역행렬을 구해서 좌표값들에 곱하면 로컬로 들어가서 머리도 000 팔도 000 방패도 000... 이렇게 된다
	//따라서 로컬로 구해서 애니메이션을 해주고 다시 TM을 곱해주면 된다.

	//if (_pParentsMat)
	//	m_matWorld *= *_pParentsMat;

	D3DXMATRIXA16 matAniPos, matAniRot;
	CalcLocalTranslationMatrix(_nKeyFrame, matAniPos);
	CalcLocalRotationMatrix(_nKeyFrame, matAniRot);

	m_matWorld = matAniRot * matAniPos;

	if (_pParentsMat)
		m_matWorld *= *_pParentsMat;

	for (int i = 0; i < m_vecChild.size(); i++)
	{
		m_vecChild[i]->Update(_nKeyFrame, &m_matWorld);
	}
}
