#pragma once
class cBigShip
{
	ID3DXMesh* Mesh = nullptr;
	vector<D3DMATERIAL9> Mtrls;
	vector<IDirect3DTexture9*> Textures;
public:
	cBigShip();
	~cBigShip();

	void Setup();
	void Render(float timeDelta);
};

