// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Skill/StrikeSkill.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MyProject/WarriorCharacter.h"

AStrikeSkill::AStrikeSkill()
{
}

void AStrikeSkill::HitCheck_Implementation()
{
	AWarriorCharacter* Warrior = Cast<AWarriorCharacter>(GetOwner());

	FVector SocketPos = Warrior->GetMesh()->GetSocketLocation(TEXT("EndH"));

	
	damageArea(200.f, this->damage, SocketPos, SocketPos);

}

void AStrikeSkill::damageArea(float radius,float damageAmount, FVector startPos, FVector endPos)
{
	Super::damageArea(radius, damageAmount,startPos,  endPos);

}
