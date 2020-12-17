#pragma once
#include "Static3DObject.h"
class Room;

class GameObjectAssemblyLine
{
private :
	Static3DObject* CreateStatic3DObject(
		string objectName,
		string sourceFileName,
		D3DXVECTOR3	position,
		D3DXVECTOR3 scale,
		D3DXVECTOR3 colliderScale,
		D3DXQUATERNION rotation = D3DXQUATERNION(0, 0, 0, 1),
		string colliderName = "basicColliderCube");

	void LoadObjectFromJson(string objectName, Room * targetRoom);


	void LoadFromJson(string fileName, Room* targetRoom);

	void CreateStartSceneGameObject(Scene* newScene);
	void CreateIngameSceneGameObject(Scene* newScene);
public :
	void MakeGameObject(Scene* newScene);
};

