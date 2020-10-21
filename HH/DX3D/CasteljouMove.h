#pragma once
class cCubeMan;

class CasteljouMove
{
private:
	std::vector<CheckPoint> m_vecCheckPoints;
	
	
public:
	CasteljouMove();
	~CasteljouMove();
	std::vector<D3DXVECTOR3> m_vecMovePoints;
	std::vector<ST_PC_VERTEX> m_vecVertexPoints;

	void AddCheckPoint(CheckPoint& point);
	void DeleteCheckPoint(int index);
	void ClearCheckPoint();
	void MoveCubeMan(cCubeMan& target);
	void CalculPath();
	void Render();

	static float biCoefficient(int top, int bot);
	static int Facto(int num);
};



