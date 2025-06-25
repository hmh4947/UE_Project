// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"
#include "InventoryComponent.h"

UItemBase::UItemBase()
{
}

UItemBase* UItemBase::CreateItemCopy() const
{
	UItemBase* ItemCopy = NewObject<UItemBase>(StaticClass());
	ItemCopy->ID = this->ID;
	ItemCopy->Quantity = this->Quantity;
	ItemCopy->ItemType = this->ItemType;
	ItemCopy->TextData = this->TextData;
	ItemCopy->NumericData = this->NumericData;
	ItemCopy->ItemStatistics = this->ItemStatistics;
	ItemCopy->AssetData = this->AssetData;

	return ItemCopy;
}

void UItemBase::SetQuantity(const int32 NewQuantity)
{/*
	//현재 수량과 동일하지 않을때
	if (NewQuantity != Quantity)
	{
		//수량이 범위 밖이라면 가장 가까운 경계값을 반환
		//스택이 가능한 경우 최대 스택 크기 0, 가능하지 않은 경우 1
		Quantity = FMath::Clamp(NewQuantity, 0, NumericData.bIsStackable ? NumericData.MaxStackSize : 1);
		if (OwningInventory)
		{
			if (Quantity <= 0)
			{
				OwningInventory->RemoveSingleInstanceOfItem(this);
			}
		}


	}
	*/
}

void UItemBase::Use(AMyCharacter* Character)
{
}
