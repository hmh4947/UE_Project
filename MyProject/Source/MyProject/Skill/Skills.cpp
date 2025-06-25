// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Skill/Skills.h"

// Sets default values
ASkills::ASkills()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ASkills::SkillExecute(ACharacter* Character)
{
	UAnimInstance* AnimInstane = Character->GetMesh()->GetAnimInstance();
	AnimInstane->Montage_Play(SkillMontage);

}

void ASkills::DamageInRadius_Implementation()
{
}

// Called when the game starts or when spawned
void ASkills::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkills::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

