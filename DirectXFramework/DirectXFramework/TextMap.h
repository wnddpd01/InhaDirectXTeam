#pragma once
class TextMap
{
private :

	UIImage* mUIBase;
	UIImage* mUICurrentLocate;

	map<eRoomName, UIImage*> mLocateUIMap;
public :
	TextMap();
	~TextMap();

	void Render(eRoomName roomName);
};

