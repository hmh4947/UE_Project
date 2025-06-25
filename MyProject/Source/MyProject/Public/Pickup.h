// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C:\Unreal_Study\UE5\UE_Project\MyProject\Source\MyProject\InteractionInterface.h"
#include "C:\Unreal_Study\UE5\UE_Project\MyProject\Source\MyProject\ItemBase.h"
#include "Pickup.generated.h"

class UItemBase;
class UDataTable;

UCLASS()
class MYPROJECT_API APickup : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	


	APickup();

	//픽업 초기화
	void InitializePickup(const TSubclassOf<UItemBase> BaseClass, const int32 InQuantity);
	void InitializeDrop(UItemBase* ItemToDrop, const int32 InQuantity);

	FORCEINLINE UItemBase* GetItemData() { return ItemReference; }

	virtual void BeginFocus() override;
	virtual void EndFocus() override;
	

protected:

	UPROPERTY(VisibleAnyWhere,Category="Pickup | Components")
	UStaticMeshComponent* PickupMesh;

	UPROPERTY(EditInstanceOnly, Category = "Pickup | Item Initialization")
	UDataTable* ItemDataTable;

	UPROPERTY(EditInstanceOnly, Category = "Pickup | Item Initialization")
	FName DesiredItemID;

	UPROPERTY(VisibleAnyWhere, Category = "Pickup | Item Reference")
	UItemBase* ItemReference;

	UPROPERTY(EditInstanceOnly, Category = "Pickup | Item Initialization")
	int32 ItemQuantity;

	UPROPERTY(VisibleInstanceOnly, Category = "Pickup | Interaction")
	FInteractableData InstanceInteractableData;

	virtual void BeginPlay() override;
	virtual void Interact(AMyCharacter* PlayerCharacter) override;
	void UpdateInteractableData();
	void TakePickup(const AMyCharacter* Taker);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
