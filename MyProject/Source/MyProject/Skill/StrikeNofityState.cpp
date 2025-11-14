// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Skill/StrikeNofityState.h"
#include "MyProject/Skill/StrikeSkill.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "MyProject/WarriorCharacter.h"

void UStrikeNofityState::BranchingPointNotifyBegin(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	
	NotifyBegin(BranchingPointPayload.SkelMeshComponent, BranchingPointPayload.SequenceAsset, BranchingPointPayload.NotifyEvent ? BranchingPointPayload.NotifyEvent->GetDuration() : 0.f);

}

void UStrikeNofityState::BranchingPointNotifyTick(FBranchingPointNotifyPayload& BranchingPointPayload, float FrameDeltaTime)
{
	AActor* OwnerActor = BranchingPointPayload.SkelMeshComponent->GetOwner();
	if (!OwnerActor)return;
	AWarriorCharacter* Warrior = Cast<AWarriorCharacter>(OwnerActor);
	if (!Warrior)return;
	//AStrikeSkill* MeleeChar = Cast<AStrikeSkill>(Warrior->CurrentSkill);
	auto* MeleeChar = Warrior->CurrentSkill;

	ASkills* Skill = Cast<ASkills>(Warrior->CurrentSkill);
	if (Skill && !Skill->bMeleeBlocked)
	{
		Skill->MeleeTrace();
	}
	/*if (MeleeChar && !MeleeChar->bMeleeBlocked) {
		MeleeChar->MeleeTrace();
		NotifyTick(BranchingPointPayload.SkelMeshComponent, BranchingPointPayload.SequenceAsset, FrameDeltaTime);

	}*/
	else {
		NotifyEnd(BranchingPointPayload.SkelMeshComponent, BranchingPointPayload.SequenceAsset, FAnimNotifyEventReference());

	}
}

void UStrikeNofityState::BranchingPointNotifyEnd(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	AWarriorCharacter* Warrior = Cast<AWarriorCharacter>(UGameplayStatics::GetPlayerCharacter(BranchingPointPayload.SkelMeshComponent->GetWorld(), 0));
	if (!Warrior)return;
	//AStrikeSkill* MeleeChar = Cast<AStrikeSkill>(Warrior->CurrentSkill);
	ASkills* MeleeChar = Cast<ASkills>(Warrior->CurrentSkill);

	if (MeleeChar) {
		MeleeChar->MeleeTracePrevious.Empty();
		MeleeChar->MeleeTraceCurrent.Empty();
		MeleeChar->bMeleeBlocked = false;
		if (MeleeChar->GetIsLoseHealth())
		{
			//Ã¼·Â ÀÒ±â
			MeleeChar->LoseHealth();
		

		}
	}


	NotifyEnd(BranchingPointPayload.SkelMeshComponent, BranchingPointPayload.SequenceAsset, FAnimNotifyEventReference());

}
