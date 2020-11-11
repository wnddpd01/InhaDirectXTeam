#pragma once

class cSkinnedMesh;
class OBB;
class QuarterMap;

class PlayerCharacter : public BaseObject, public BaseObserver
{
public:
	void Setup();
	void Update() override;
	void Render() override;

	bool Update(eEventName eventName, void* parameter) override;

	OBB* GetOBB();

	D3DXVECTOR3 & GetPosition();

	void SetCollsion(bool Collision);
	
	PlayerCharacter();
	virtual ~PlayerCharacter();
private:
	cSkinnedMesh* m_pSkinnedMesh;
	OBB* m_pOBB;
	QuarterMap* mQuarterMap;
	D3DXVECTOR3 m_vDirection;
	D3DXVECTOR3 m_vPosition;
	D3DXMATRIXA16 m_matWorld;
	D3DXMATRIXA16 matR;
	bool isCollision;
};

