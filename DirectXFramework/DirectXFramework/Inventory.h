#pragma once
class Inventory
{
	enum eInventorySlot
	{
		Recovery = 0, Useful, Key, SLOT_COUNT
	};
	UIImage * mUISlotImage[static_cast<int>(SLOT_COUNT)];
	Base3DObject* mSlotItem[static_cast<int>(SLOT_COUNT)];
public :
	Inventory();
	~Inventory();
	
	void Setup();
	void Update();
	void Render();

	void AddItem(Base3DObject* item);
	void UseItem(eInventorySlot eSlot);
	
};