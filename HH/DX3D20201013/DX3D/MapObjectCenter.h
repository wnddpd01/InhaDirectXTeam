#pragma once
class MapObject;

class MapObjectCenter
{
private:
	vector<MapObject*> m_pVecMapObj;
	
public:
	MapObjectCenter();
	~MapObjectCenter();
	
	vector<MapObject*>& GetVecMapObj();
	void AddMapObj(MapObject* p);
	void Setup();
	void Update();
	void Render();
};


