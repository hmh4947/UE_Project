// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Skill/StrikeSkill.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MyProject/WarriorCharacter.h"
#include "MyProject/ClickMovePlayerController.h"
#include "DrawDebugHelpers.h"
AStrikeSkill::AStrikeSkill()
{
}

void AStrikeSkill::BeginPlay()
{
	Super::BeginPlay();
	ActiveSkill();
}

void AStrikeSkill::HitCheck_Implementation()
{
	AWarriorCharacter* Warrior = Cast<AWarriorCharacter>(GetOwner());

	FVector SocketPos = Warrior->GetActorLocation();
	
	damageArea(200.f, this->damage, SocketPos, SocketPos);

}

void AStrikeSkill::MeleeTrace()
{
	//isLoseHealth = false;
	Super::MeleeTrace();
}

void AStrikeSkill::LoseHealth()
{
	Super::LoseHealth();
}



void AStrikeSkill::damageArea(float radius,float damageAmount, FVector startPos, FVector endPos)
{
	Super::damageArea(radius, damageAmount,startPos,  endPos);

}

