// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Skill/SwordSmashSkill.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MyProject/WarriorCharacter.h"

ASwordSmashSkill::ASwordSmashSkill()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASwordSmashSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GetRemainingTime();
}


void ASwordSmashSkill::BeginPlay()
{
	Super::BeginPlay();
	ActiveSkill();
	
}

void ASwordSmashSkill::HitCheck_Implementation()
{
	AWarriorCharacter* Warrior = Cast<AWarriorCharacter>(GetOwner());
	FVector SocketPos = Warrior->GetMesh()->GetSocketLocation(TEXT("EndH"));
	
	damageArea(1000.f,this->damage, SocketPos, SocketPos);
	
}

void ASwordSmashSkill::damageArea(float radius,float damageAmount, FVector startPos, FVector endPos)
{
	Super::damageArea(radius, damageAmount, startPos, endPos);
 
}


