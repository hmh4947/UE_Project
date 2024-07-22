// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeAnimNotifyState.h"
#include "WarriorCharacter.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

void UMeleeAnimNotifyState::BranchingPointNotifyBegin(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	NotifyBegin(BranchingPointPayload.SkelMeshComponent, BranchingPointPayload.SequenceAsset, BranchingPointPayload.NotifyEvent ? BranchingPointPayload.NotifyEvent->GetDuration() : 0.f);
}

void UMeleeAnimNotifyState::BranchingPointNotifyTick(FBranchingPointNotifyPayload& BranchingPointPayload, float FrameDeltaTime)
{
	AWarriorCharacter* MeleeChar = Cast<AWarriorCharacter>(UGameplayStatics::GetPlayerCharacter(BranchingPointPayload.SkelMeshComponent->GetWorld(), 0));

	if (MeleeChar && !MeleeChar->bMeleeBlocked) {
		MeleeChar->MeleeTrace();
		NotifyTick(BranchingPointPayload.SkelMeshComponent, BranchingPointPayload.SequenceAsset, FrameDeltaTime);
	}
	else {
		NotifyEnd(BranchingPointPayload.SkelMeshComponent, BranchingPointPayload.SequenceAsset);
	}
}

void UMeleeAnimNotifyState::BranchingPointNotifyEnd(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	AWarriorCharacter* MeleeChar = Cast<AWarriorCharacter>(UGameplayStatics::GetPlayerCharacter(BranchingPointPayload.SkelMeshComponent->GetWorld(), 0));
	if (MeleeChar) {
		MeleeChar->MeleeTracePrevious.Empty();
		MeleeChar->MeleeTraceCurrent.Empty();
		MeleeChar->bMeleeBlocked = false;
	}

	NotifyEnd(BranchingPointPayload.SkelMeshComponent, BranchingPointPayload.SequenceAsset);
}
