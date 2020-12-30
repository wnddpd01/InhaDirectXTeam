#include "stdafx.h"
#include "TextMap.h"

TextMap::TextMap()
{
	mUIBase = new UIImage("Resources/UI/TextMap/mapNotice.png", {50, 2}, 12, 2);
	mUIBase->SetVisible(true);

	mLocateUIMap.insert(make_pair(eRoomName::R2A01, new UIImage("Resources/UI/TextMap/복도.png", { 53, 2 }, 6, 2)));
	mLocateUIMap.insert(make_pair(eRoomName::R2A02, new UIImage("Resources/UI/TextMap/탕비실.png", { 53, 2 }, 6, 2)));
	mLocateUIMap.insert(make_pair(eRoomName::R2A03, new UIImage("Resources/UI/TextMap/사무실A.png", { 53, 2 }, 6, 2)));
	mLocateUIMap.insert(make_pair(eRoomName::R2A04, new UIImage("Resources/UI/TextMap/사무실A.png", { 53, 2 }, 6, 2)));
	mLocateUIMap.insert(make_pair(eRoomName::R2A05, new UIImage("Resources/UI/TextMap/회의실.png", { 53, 2 }, 6, 2)));
	mLocateUIMap.insert(make_pair(eRoomName::R2A06, new UIImage("Resources/UI/TextMap/대표이사실.png", { 53, 2 }, 6, 2)));
	mLocateUIMap.insert(make_pair(eRoomName::R2A07, new UIImage("Resources/UI/TextMap/사장실.png", { 53, 2 }, 6, 2)));
	mLocateUIMap.insert(make_pair(eRoomName::R2B01, new UIImage("Resources/UI/TextMap/복도.png", { 53, 2 }, 6, 2)));
	mLocateUIMap.insert(make_pair(eRoomName::R2B02, new UIImage("Resources/UI/TextMap/사무실B.png", { 53, 2 }, 6, 2)));
	mLocateUIMap.insert(make_pair(eRoomName::R2B03, new UIImage("Resources/UI/TextMap/서버실.png", { 53, 2 }, 6, 2)));
	mLocateUIMap.insert(make_pair(eRoomName::R2C01, new UIImage("Resources/UI/TextMap/복도.png", { 53, 2 }, 6, 2)));
	mLocateUIMap.insert(make_pair(eRoomName::R2C02, new UIImage("Resources/UI/TextMap/홀.png", { 53, 2 }, 6, 2)));
	mLocateUIMap.insert(make_pair(eRoomName::R2C03, new UIImage("Resources/UI/TextMap/회의실.png", { 53, 2 }, 6, 2)));

	for (map<eRoomName, UIImage*>::value_type& locateText : mLocateUIMap)
	{
		locateText.second->SetVisible(true);
	}
}

TextMap::~TextMap()
{
}

void TextMap::Render(eRoomName* roomName)
{
	mUIBase->Render();

	if(roomName != nullptr && mLocateUIMap.find(*roomName) != mLocateUIMap.end())
	{
		mLocateUIMap[*roomName]->Render();
	}
}


