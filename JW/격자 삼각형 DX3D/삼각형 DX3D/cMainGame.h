#pragma once


class cMainGame
{
public:
	cMainGame();
	~cMainGame();


private:
	vector<ST_PC_VERTEX> m_vecLineVertex;
	vector<ST_PC_VERTEX> m_vecTriangleVertex;
	
public:
	void Setup();
	void Update();
	void Render();
	void Cleanup();


	void Setup_Line();
	void Draw_Line();

	void Setup_Triangle();
	void Draw_Triangle();
	
};

