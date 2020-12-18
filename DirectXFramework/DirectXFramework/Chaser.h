#pragma once
#include "Base3DObject.h"

class SkinnedMesh;
class Chaser :
	public Base3DObject
{
private :
	SkinnedMesh* mSkinnedMesh;
public :
	Chaser();
	~Chaser();

	void Update() override;
	void Render() override;
};

