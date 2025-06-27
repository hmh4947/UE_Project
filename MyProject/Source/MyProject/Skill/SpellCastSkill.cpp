// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Skill/SpellCastSkill.h"


ASpellCastSkill::ASpellCastSkill()
{

}

void ASpellCastSkill::HitCheck_Implementation()
{
	AWarriorCharacter* Warrior = Cast<AWarriorCharacter>(GetOwner());

    FVector Start, End, Direction;
    FVector CharacterLocation = Warrior->GetActorLocation();

    FRotator CurrentRotator = Warrior->GetActorRotation();
    Direction = CurrentRotator.Vector();
    End = CharacterLocation + Direction * 500.f;

	damageArea(150.f, this->damage, End, End);

}

void ASpellCastSkill::damageArea(float radius, float damageAmount, FVector startPos, FVector endPos)
{
	Super::damageArea(radius, damageAmount, startPos, endPos);

}

