// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Engine/DataTable.h>
#include "ST_Items.generated.h"

/*
UENUM(BlueprintType)
enum class ItemType :uint8
{
	Consumable UMETA(DisplayName = "Consumable"), //¼Ò¸ð
	Quest UMETA(DisplayName = "Quest") //Äù½ºÆ®
};
/*
class MYPROJECT_API ST_Consumable_Items
{
public:
	ST_Consumable_Items();
	~ST_Consumable_Items();
};
*/
USTRUCT(BlueprintType)
struct FST_Items: public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	UTexture2D* Icon;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString Description;

	/*UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	ItemType ItemType;
	*/
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int Heal;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int Buy;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int Sell;

	
	
};
