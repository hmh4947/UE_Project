// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyProjectGameModeBase.generated.h"

/**
 * 
 */
class AMyCharacter;
class AEnemyCharacter;
class AActor;
UCLASS()
class MYPROJECT_API AMyProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void ResetEnvironment();

	void SetPlayer(AMyCharacter* character);
	void SetEnemy(AEnemyCharacter* enemyCharacter);

	
private:
	AMyCharacter* player;
	AEnemyCharacter* enemy;
	

};
