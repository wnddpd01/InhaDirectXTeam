#pragma once
#include "cCubeMan.h"
class cCubeAutoMan :
	public cCubeMan
{
	vector<ST_PC_VERTEX> vertices_;
	int currentVertex;
public:
	cCubeAutoMan();
	~cCubeAutoMan();

	void Setup(vector<ST_PC_VERTEX>& vertices);
	void Update() override;
};

