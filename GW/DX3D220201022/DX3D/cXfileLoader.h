#pragma once
class cXfileLoader
{
public:
	cXfileLoader();
	~cXfileLoader();
private:
	ID3DXMesh* Mesh;
	vector<D3DMATERIAL9> Mtrls;
	vector<IDirect3DTexture9*> Textures;
public:
	bool Setup();
	bool Display(float timeDelta);

};

