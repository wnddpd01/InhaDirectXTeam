#pragma once

class cPyramid;

class cHexagon
{
	void SetBezier(int num, size_t t, vector<ST_PC_VERTEX>& vertex);
	vector<cPyramid*>	pyramids_;
	
public:
	vector<ST_PC_VERTEX> st_pc_vertices_;
	vector<ST_PC_VERTEX> st_pc_bezier_vertices_;
	cHexagon();
	~cHexagon();

	void Setup();
	void Update();
	void Render();
};

