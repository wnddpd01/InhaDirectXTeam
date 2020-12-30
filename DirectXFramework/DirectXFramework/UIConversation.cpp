#include "stdafx.h"
#include "UIConversation.h"


UIConversation::UIConversation()
	:UIImage("Resources/UI/Setting/Conver2.png", { 0, 0 }, 64, 36)
	, OutputText("")
{

	D3DXCreateFont(
		gD3Device,               //�׷��� ī�� �������̽�
		50,                              // ���� ���� ũ��
		25,                               // ���� ���� ũ��
		500,                            // ���� 0~1000����
		1,                                // �Ӹʰ� ����ϰ� ���Ǵ� �� . 1�� �ش�
		false,                           // ���ڸ� ( ���� ) 
		DEFAULT_CHARSET,       // �ϴ� �̰�����...
		OUT_DEFAULT_PRECIS,   // ���е�
		DEFAULT_QUALITY,        // �ϴ� �̰�����...
		0,                                // �ϴ� �̰�����...
		L"�Ÿ���",                      // ��� �۲�
		&mFont);
}

UIConversation::~UIConversation()
{
}

void UIConversation::SetConversation(string newText)
{
	this->SetVisible(true);
	OutputText = newText;
}

void UIConversation::Render()
{
	if (mbVisible)
	{
		UIImage::Render();
		RECT rc = { 100, 650, -1, -1 };
		mFont->DrawTextA(NULL, OutputText.c_str(), -1, &rc, DT_LEFT | DT_NOCLIP, 0xff000000);
	}
}


