#include "stdafx.h"
#include "Player.h"
#include "UIImage.h"
#include "Scene.h"


Player::Inventory::Inventory()
	: mKey(nullptr)
	, mbGetKey(false)
	, mInventory1(nullptr)
	, mInventory2(nullptr)
	, mInventory3(nullptr)
{
	Setup();
}

Player::Inventory::~Inventory()
{
	SAFE_DELETE(mKey);
	SAFE_DELETE(mInventory1);
	SAFE_DELETE(mInventory2);
	SAFE_DELETE(mInventory3);
}

void Player::Inventory::Setup()
{
	mKey = new UIImage(string("Resources/Item/key.png"));
	mKey->SetObjectName("key");
	mKey->SetPos(D3DXVECTOR3(mKey->GetPos().x + mKey->GetWidth()*2.8f, mKey->GetPos().y + 15.f, 0));
}

void Player::Inventory::DrawInventoryUI(Scene& scene)
{
	mInventory1 = new UIImage("Resources/UI/Inventory.png");
	mInventory1->SetObjectName("inventory");
	mInventory1->SetPos(D3DXVECTOR3(mInventory1->GetPos().x,mInventory1->GetPos().y, 0.0f));
	mInventory1->SetVisible(true);
	scene.mGameUIs.insert(make_pair("inventory", mInventory1));

	mInventory2 = new UIImage("Resources/UI/Inventory.png");
	mInventory2->SetObjectName("inventory2");
	mInventory2->SetPos(D3DXVECTOR3(mInventory2->GetPos().x + mInventory2->GetWidth(),mInventory2->GetPos().y, 0.0f));
	mInventory2->SetVisible(true);
	scene.mGameUIs.insert(make_pair("inventory2", mInventory2));

	mInventory3 = new UIImage("Resources/UI/Inventory.png");
	mInventory3->SetObjectName("inventory3");
	mInventory3->SetPos(D3DXVECTOR3(mInventory3->GetPos().x + mInventory3->GetWidth()*2.f,mInventory3->GetPos().y, 0.0f));
	mInventory3->SetVisible(true);
	scene.mGameUIs.insert(make_pair("inventory3", mInventory3));
}


void Player::Inventory::Update()
{
	if(!mbGetKey)
	{
		mKey->SetVisible(false);
	}
	else
	{
		mKey->SetVisible(true);
	}



}

void Player::Inventory::Render()
{
	if (mKey)
	{
		mKey->Render();
	}

}


void Player::Inventory::SetInItem(BOOL state, string ObjectName)
{
	if (ObjectName == "key")
	{
		mbGetKey = state;
	}

}

bool Player::Inventory::GetInItem(string ObjectName)
{
	if (ObjectName == "key")
	{
		return mbGetKey;
	}

}

void Player::Inventory::UseItem(Base3DObject& Object)
{
	if (Object.GetTypeTag() == eTypeTag::DOOR &&  GetInItem("key"))
	{
		Object.SetStateTag(eStateTag::DOOR_OPEN);
		SetInItem(false, "key");
	}
}

