#pragma once


class cMainGame
{
public:
	cMainGame();
	~cMainGame();


private:
	vector<ST_PC_VERTEX> m_vecLineVertex;			// vector<ST_PC_VERTEX> 는 구조체이고  D3DXVECTOR3 구조체의 객체 p,c 갖고있음
	vector<ST_PC_VERTEX> m_vecTriangleVertex;		// enum으로 FVF도 가짐


	D3DXVECTOR3 matRot;
	D3DXVECTOR3 Angle;
	D3DXVECTOR3 vDirection;
	D3DXVECTOR3 matTrans;


	
public:
	void Setup();	// 여기서 큐브 초기 설정
	void Update();	// 큐브 업데이트
	void Render();	// 그려주고
	void Cleanup();

	void Setup_Line();
	void Draw_Line();

	void Setup_Triangle();
	void Draw_Triangle();


	//=========== winapi 함수들 =================

	
	
	
	void Update_Move();		// 이동 처리     이게 업데이트 안에 들어있어ㅎㅁ
	void Update_Rotation(); // 회전 처리
	
	//=====================
};

