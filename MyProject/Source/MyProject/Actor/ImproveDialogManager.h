// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ImproveDialogManager.generated.h"
class UDialogWidget;
class UDialogNodeAsset;

UCLASS()
class MYPROJECT_API AImproveDialogManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AImproveDialogManager();
	UPROPERTY(EditAnywhere, Category = "Dialog")
	UDialogNodeAsset* StartNode;

	UPROPERTY(EditAnywhere, Category = "Dialog")
	TSubclassOf<UDialogWidget> DialogWidgetClass;

	UPROPERTY()
	UDialogWidget* CurrentWidget;

	UPROPERTY()
	UDialogNodeAsset* CurrentNode;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
