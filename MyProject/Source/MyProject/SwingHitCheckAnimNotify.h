// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SevargoEnemy.h"
#include "SwingHitCheckAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API USwingHitCheckAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
private:

	UPROPERTY(VisibleAnyWhere)
	UStaticMeshComponent* WeaponMesh;




};
