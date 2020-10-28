#pragma once

#define g_pFontManager cFontManager::GetInstance()

class cFontManager
{
public:

	enum eFontType
	{
		E_DEFAULT,
		E_QUEST,
	};
private:
	
	map<eFontType, LPD3DXFONT> m_mapFont;
public:
	Singletone(cFontManager);

public :
	LPD3DXFONT GetFont(eFontType e);
	void Destroy();
};

