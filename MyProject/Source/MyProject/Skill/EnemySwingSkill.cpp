// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Skill/EnemySwingSkill.h"
#include "MyProject/SevargoEnemy.h"
#include "Kismet/KismetSystemLibrary.h"

AEnemySwingSkill::AEnemySwingSkill()
{
}

void AEnemySwingSkill::BeginPlay()
{
	
}

void AEnemySwingSkill::HitCheck_Implementation()
{
	
	ASevargoEnemy* Enemy = Cast<ASevargoEnemy>(GetOwner());

	FVector SocketPos = Enemy->GetMesh()->GetSocketLocation(TEXT("WeaponHit_Socket"));


	damageArea(150.f, this->damage, SocketPos, SocketPos);
}

void AEnemySwingSkill::damageArea(float radius, float damageAmount, FVector startPos, FVector endPos)
{
	Super::damageArea(radius, damageAmount, startPos, endPos);
	
}


