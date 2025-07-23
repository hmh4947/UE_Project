// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Skill/SpawnDeerSkill.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MyProject/WarriorCharacter.h"
#include "MyProject/ClickMovePlayerController.h"
#include "DrawDebugHelpers.h"

ASpawnDeerSkill::ASpawnDeerSkill()
{
	
}

void ASpawnDeerSkill::BeginPlay()
{
	Super::BeginPlay();
	ActiveSkill();
}

void ASpawnDeerSkill::HitCheck_Implementation()
{
}

void ASpawnDeerSkill::MeleeTrace()
{
	Super::MeleeTrace();
}

void ASpawnDeerSkill::LoseHealth()
{
	Super::LoseHealth();
}

