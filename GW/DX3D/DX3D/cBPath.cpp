#include "stdafx.h"
#include "cBPath.h"
#include "cCubeMan.h"
#include "cPyramid.h"

cBPath::cBPath()
	:m_pCubeMan(NULL)
{
	
}


cBPath::~cBPath()
{
	SafeDelete(m_pCubeMan);
	
}


void cBPath::Setup()
{

	m_pCubeMan = new cCubeMan;
	m_pCubeMan->Setup();

}



void cBPath::Render()
{

	if (m_pCubeMan)
		m_pCubeMan->Render();
	
}

void cBPath::resurlt()
{


	
}
