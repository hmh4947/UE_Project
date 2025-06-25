// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Skill/SkillComponent.h"

// Sets default values for this component's properties
USkillComponent::USkillComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USkillComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	for (int32 i = 0; i < StartSkillsClass.Num(); i++)
	{
		ActivatableSkills.Add(GetWorld()->SpawnActor<ASkills>(StartSkillsClass[i]));
		ActivatableSkills[i]->SetOwner(GetOwner());
		//이름으로 스킬찾기위해 배열에 넣음
	//	ActivatableSkillNames.Add(ActivatableSkills[i]->SkillName);
	}

}


// Called every frame
void USkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USkillComponent::Skill(ACharacter* Character, const ESkillInput& SkillInput)
{
	for (ASkills* Skill : ActivatableSkills)
	{
		if (Skill->SkillInput == SkillInput)
		{
			startSkill(Character, SkillInput, Skill);
		}
	}
}

void USkillComponent::startSkill(ACharacter* Character, const ESkillInput& SkillInput, ASkills* skill)
{
	if (skill)
	{
		skill->SkillExecute(Character);
		skill->DamageInRadius_Implementation();
	}
}

