// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Skill/SkillComponent.h"
#include "MyProject/WarriorCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyProject/ClickMovePlayerController.h"

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

	setCurrentSkill(ActivatableSkills[0]);


	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return;

	AAIController* AIController = Cast<AAIController>(OwnerPawn->GetController());
	if (!AIController) return;

	UBlackboardComponent* Blackboard = AIController->GetBlackboardComponent();
	if (!Blackboard) return;


	Blackboard->SetValueAsObject("SkillObj", ActivatableSkills[0]);
	InitActivatableSkill.Broadcast();

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
		if (Skill->SkillInput == SkillInput && Skill->GetIsActiveSkill()) 
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

TObjectPtr<ASkills>& USkillComponent::GetActivatableSkill(int32 Index)
{
	return ActivatableSkills[Index];
}

void USkillComponent::UpdateSkillCool()
{
	AWarriorCharacter* warriorCharacter = Cast<AWarriorCharacter>(GetOwner());
	AClickMovePlayerController* PlayerController = Cast<AClickMovePlayerController>(warriorCharacter->GetController());
	for (ASkills* Skill : ActivatableSkills)
	{
	
		if(Skill->SkillInput==ESkillInput::ESI_InputQ)
		{
		
			PlayerController->UpdateQSkillCoolDown(Skill->GetRemainingTime(),Skill);
			
		}
		if (Skill->SkillInput == ESkillInput::ESI_InputW)
		{
			PlayerController->UpdateWSkillCoolDown(Skill->GetRemainingTime(), Skill);
		}
		if (Skill->SkillInput == ESkillInput::ESI_InputE)
		{
			PlayerController->UpdateESkillCoolDown(Skill->GetRemainingTime(), Skill);
		}
		if (Skill->SkillInput == ESkillInput::ESI_InputR)
		{
			PlayerController->UpdateRSkillCoolDown(Skill->GetRemainingTime(), Skill);
		}
	}
}

void USkillComponent::startSkill(ACharacter* Character, const ESkillInput& SkillInput, ASkills* skill)
{
	AWarriorCharacter* warriorCharacter = Cast<AWarriorCharacter>(GetOwner());
	AClickMovePlayerController* PlayerController = Cast<AClickMovePlayerController>(warriorCharacter->GetController());
	if (!skill) return;
	if(!skill->GetIsActiveSkill()) return;
	
	warriorCharacter->SetIsAttacking(true);
	setCurrentSkill(skill);
	skill->SkillExecute(Character);
	skill->StartTimer();
	UpdateSkillCool();
	GetWorld()->GetTimerManager().SetTimer(RemainingTimerHandler, this, &USkillComponent::UpdateSkillCool, 1.0f, true, 1.0f);
	
	
}

