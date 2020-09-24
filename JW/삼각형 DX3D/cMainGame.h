#pragma once


class cMainGame
{
public:
	cMainGame();
	~cMainGame();


private:
	vector<ST_PC_VERTEX> m_vecLineVertex;			// vector<ST_PC_VERTEX> �� ����ü�̰�  D3DXVECTOR3 ����ü�� ��ü p,c ��������
	vector<ST_PC_VERTEX> m_vecTriangleVertex;		// enum���� FVF�� ����


	D3DXVECTOR3 matRot;
	D3DXVECTOR3 Angle;
	D3DXVECTOR3 vDirection;
	D3DXVECTOR3 matTrans;


	
public:
	void Setup();	// ���⼭ ť�� �ʱ� ����
	void Update();	// ť�� ������Ʈ
	void Render();	// �׷��ְ�
	void Cleanup();

	void Setup_Line();
	void Draw_Line();

	void Setup_Triangle();
	void Draw_Triangle();


	//=========== winapi �Լ��� =================

	
	
	
	void Update_Move();		// �̵� ó��     �̰� ������Ʈ �ȿ� ����־��
	void Update_Rotation(); // ȸ�� ó��
	
	//=====================
};

