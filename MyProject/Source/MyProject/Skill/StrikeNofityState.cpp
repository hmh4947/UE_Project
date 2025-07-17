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
	AStrikeSkill* MeleeChar = Cast<AStrikeSkill>(Warrior->CurrentSkill);

	if (MeleeChar && !MeleeChar->bMeleeBlocked) {
		MeleeChar->MeleeTrace();
		NotifyTick(BranchingPointPayload.SkelMeshComponent, BranchingPointPayload.SequenceAsset, FrameDeltaTime);

	}
	else {
		NotifyEnd(BranchingPointPayload.SkelMeshComponent, BranchingPointPayload.SequenceAsset);

	}
}

void UStrikeNofityState::BranchingPointNotifyEnd(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	AWarriorCharacter* MeleeChar = Cast<AWarriorCharacter>(UGameplayStatics::GetPlayerCharacter(BranchingPointPayload.SkelMeshComponent->GetWorld(), 0));
	if (MeleeChar) {
		MeleeChar->MeleeTracePrevious.Empty();
		MeleeChar->MeleeTraceCurrent.Empty();
		MeleeChar->bMeleeBlocked = false;
		if (MeleeChar->isLoseHealth)
		{
			//Ã¼·Â ÀÒ±â
			MeleeChar->losehealth();
		

		}
	}


	NotifyEnd(BranchingPointPayload.SkelMeshComponent, BranchingPointPayload.SequenceAsset);

}
