// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Skill/SwordSmashSkill.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MyProject/WarriorCharacter.h"

ASwordSmashSkill::ASwordSmashSkill()
{
}

void ASwordSmashSkill::DamageInRadius_Implementation()
{
	UE_LOG(LogTemp, Display, TEXT("RADIUS"));
}

void ASwordSmashSkill::HitCheck()
{

    damageArea(300.f);
}

void ASwordSmashSkill::damageArea(float radius)
{
    FVector start = FVector(50.f, 50.f, 50.f);
    FVector end = FVector(150.f, 150.f, 150.f);
   

}

