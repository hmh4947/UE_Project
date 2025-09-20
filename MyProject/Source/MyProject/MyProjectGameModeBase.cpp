// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyProjectGameModeBase.h"
#include "MyProject/MyCharacter.h"
#include "MyProject/EnemyCharacter.h"


void AMyProjectGameModeBase::ResetEnvironment()
{
	if (player)
	{
		player->Initialize();
		player->SetActorLocation(FVector(-2500.f,-120.f,240.f));

	}
	if (enemy)
	{
		enemy->Initialize();
	}
}

void AMyProjectGameModeBase::SetPlayer(AMyCharacter* character)
{
	this->player = character;
}

void AMyProjectGameModeBase::SetEnemy(AEnemyCharacter* enemyCharacter)
{
	this->enemy = enemyCharacter;
}
