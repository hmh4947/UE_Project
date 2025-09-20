// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject/Actor/LevelSteamingActor.h"
#include "VideoWidgetActor.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AVideoWidgetActor : public ALevelSteamingActor
{
	GENERATED_BODY()

public:

	AVideoWidgetActor();

	virtual void BeginPlay() override;

protected:

	
	void ClosedWidget() override;
};
