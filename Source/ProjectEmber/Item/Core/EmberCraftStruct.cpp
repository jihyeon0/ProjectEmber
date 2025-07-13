// Fill out your copyright notice in the Description page of Project Settings.


#include "EmberCraftStruct.h"

#include "EmberTmpStruct.h"
#include "ItemCraftType.h"

void FTotalItemInfo::AddItem(const int32 InQuantity, const int32 InIndex)
{
	if (InQuantity > 0)
	{
		TotalQuantity += InQuantity;
		ItemIndexes.Add(InIndex);
	}
}

int32 FTotalItemInfo::RemoveItemQuantity(const int32 InQuantity)
{
	int32 RemoveQuantity = 0;

	if (InQuantity > 0)
	{
		RemoveQuantity = FMath::Min(TotalQuantity,InQuantity);;
		TotalQuantity -= RemoveQuantity;
	}
	return RemoveQuantity;
}

void FTotalItemInfo::RemoveItemIndexes(const int32 InIndex)
{
	ItemIndexes.Remove(InIndex);
}


FCraftSelectInfo::FCraftSelectInfo(const FCraftInfoRow& InCraftInfoRow)
{
	ResultItemData = FEmberSlot(InCraftInfoRow.ResultItem.ItemData.RowName, InCraftInfoRow.ResultItem.Quantity);
	RequiredItemDataHandles = InCraftInfoRow.RequireItems;
}
