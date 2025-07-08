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

	}
	InitActivatableSkill.Broadcast();

	setCurrentSkill(ActivatableSkills[0]);
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
		if (Skill->SkillInput == SkillInput&&Skill->GetIsActiveSkill()) 
		{
			startSkill(Character, SkillInput, Skill);
		}
		
	}
}

void USkillComponent::setCurrentSkill(ASkills* skill)
{
	currentSkill = skill;
}

ASkills* USkillComponent::getCurrentSkill() const
{
	return currentSkill;
}

const TArray<TObjectPtr<ASkills>>& USkillComponent::GetActivatableSkills() const
{
	return ActivatableSkills; 
}

void USkillComponent::startSkill(ACharacter* Character, const ESkillInput& SkillInput, ASkills* skill)
{
	if (!skill) return;
	if(!skill->GetIsActiveSkill()==true) return;
	{
		setCurrentSkill(skill);
		skill->SkillExecute(Character);
	//	skill->StartTimer();
		
	}
}

