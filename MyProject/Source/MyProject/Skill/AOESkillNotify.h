// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AOESkillNotify.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UAOESkillNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:

	UPROPERTY(VisibleAnyWhere)
	UStaticMeshComponent* WeaponMesh;

};
