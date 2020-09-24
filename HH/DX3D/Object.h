#pragma once
class Object
{
private:
	D3DXVECTOR3 vPosition;
	D3DXVECTOR3 vRotation;
	D3DXVECTOR3 vScale;
	D3DXVECTOR3 m_dir;
	
	std::vector<ST_PC_VERTEX> m_vecGizmoVertex;
	std::vector<ST_TRIANGLE> m_vecGizmoTriangle;
	
	std::vector<ST_PC_VERTEX> m_vecVertex;
	std::vector<ST_TRIANGLE> m_vecTriangle;
	int m_shape;
	int colorCnt = 0;
	int colorCnt2 = 0;

	D3DCOLOR color[6];

	void SetGizmo();
	void DrawGizmo();
	
public:
	Object(int shape);
	~Object();

	void SetUp();
	void UpDate();
	void Render();

	void MovePositon(float plusDistance);
	void Rotate(float plusAngle);
};

