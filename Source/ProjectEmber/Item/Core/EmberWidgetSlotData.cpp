// Fill out your copyright notice in the Description page of Project Settings.


#include "EmberWidgetSlotData.h"

#include "EmberItemStruct.h"
#include "EmberTmpStruct.h"


FEmberWidgetSlotData::FEmberWidgetSlotData(const FInstancedStruct& InSlotData)
{
	if (const FEmberSlotData* Slot = InSlotData.GetPtr<FEmberSlotData>())
	{
		ItemID = Slot->ItemID;
		Quantity = Slot->Quantity;
		MaxStackSize = Slot->MaxStackSize;
		ItemDisplayName = Slot->ItemDisplayName;
		ItemDescription = Slot->ItemDescription;
		Enchants = Slot->EnchantEffects;
		if (Slot->SlotData)
		{
			if (const FSlotInfoRow* SlotInfoRow = Slot->SlotData->GetRow<FSlotInfoRow>("SlotInfo"))
			{
				ItemIcon = SlotInfoRow->ItemIcon;
			}
		}
	}
}
