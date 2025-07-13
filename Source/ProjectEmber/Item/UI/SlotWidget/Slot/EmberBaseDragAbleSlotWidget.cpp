// Fill out your copyright notice in the Description page of Project Settings.


#include "EmberBaseDragAbleSlotWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "EmberLog/EmberLog.h"
#include "Item/ItemContainer/EmberBaseSlotContainer.h"
#include "Item/UI/DragDropOperation/EmberItemSlotDragDropOperation.h"
#include "Item/UI/SlotWidget/DragSlotImage.h"

void UEmberBaseDragAbleSlotWidget::CreateDragDropOperation_Implementation(const FGeometry& InGeometry,
                                                           const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	if (TObjectPtr<UEmberItemSlotDragDropOperation> SlotOperation = NewObject<UEmberItemSlotDragDropOperation>(GetTransientPackage(), UEmberItemSlotDragDropOperation::StaticClass()))
	{
		SlotOperation->SlotIndex = SlotIndex;
		SlotOperation->Pivot = EDragPivot::MouseDown;
		SlotOperation->DraggedQuantity = SlotData.Quantity;
		SlotOperation->Provider = DataProvider;
		if (!SlotOperation->Provider)
		{
			EMBER_LOG(LogEmberItem, Warning, TEXT("SlotOperationProvider Is Null"));
		}
		if (DragSlotImageClass)
		{
			if (TObjectPtr<UDragSlotImage> CopySlotImage = CreateWidget<UDragSlotImage>(this, DragSlotImageClass))
			{
				CopySlotImage->InitImage(SlotImage);
				SlotOperation->DefaultDragVisual = CopySlotImage;
			}
		}
    
		OutOperation = SlotOperation;
	}
}

FEventReply UEmberBaseDragAbleSlotWidget::StartDragDrop_Implementation(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (!SlotData.bIsEmpty() && InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		// 클릭 즉시 drag발동
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
		/*// 클릭하면서 움직임이있을경우 발동
		FEventReply Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, InMouseEvent.GetEffectingButton());
		return Reply.NativeReply;*/
	}
	return UWidgetBlueprintLibrary::Unhandled();
}

bool UEmberBaseDragAbleSlotWidget::DropAction_Implementation(const FGeometry& InGeometry,
	const FPointerEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (TObjectPtr<const UEmberItemSlotDragDropOperation> EmberDropOperation = Cast<UEmberItemSlotDragDropOperation>(InOperation))
	{
		if (!EmberDropOperation->Provider || !Cast<UEmberBaseSlotContainer>(DataProvider.GetObject()))
		{
			return false;
		}
		IEmberSlotProviderInterface::Execute_MoveItemByWidget(DataProvider.GetObject(), EmberDropOperation->SlotType, SlotIndex, EmberDropOperation->Provider.GetObject(), EmberDropOperation->SlotIndex, EmberDropOperation->DraggedQuantity);
	}
	return true;
}
