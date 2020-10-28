#pragma once

typedef struct MouseEvent
{
	POINT mousePt;
	bool bClicked;
	bool isUsed;
	MouseEvent()
		: mousePt({0, 0})
		, bClicked(false)
		, isUsed(false)
	{}
};

class cUI
{
protected:
	vector<cUI *> m_vecChild;
public:
	cUI();
	virtual ~cUI();

	D3DXMATRIXA16 m_matWorld;
	D3DXVECTOR3 m_pos;
	float		m_width;
	float		m_height;
	bool isVisible;

	void AddChild(cUI * child);
	
	virtual void Update(MouseEvent mouseEvent);
	virtual void Render(D3DXMATRIXA16* parentMat = NULL);
};

