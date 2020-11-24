#pragma once

enum class eSceneName;
class Scene;
class Static3DObject;

class SceneFactory
{
public:
	SceneFactory();
	~SceneFactory();

	Scene* CreateScene(eSceneName eSceneName);

	Static3DObject* CreateStatic3DObject(
		string objectName,
		string sourceFileName,
		D3DXVECTOR3	position,
		D3DXQUATERNION rotation = D3DXQUATERNION(0,0,0,0),
		string colliderName = "basicColliderCube");

};

