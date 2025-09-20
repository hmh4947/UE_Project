// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyProject.h"
#include "Animation/AnimInstance.h"
#include "WarriorAnimInstance.generated.h"

//여러개를 엮을 수 있는 델리게이트
DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);
/**
 * 
 */
UCLASS()
class MYPROJECT_API UWarriorAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	

public:

	UWarriorAnimInstance();

	void PlayAttackMontage();

	//다음 어택 몽타주로 이동
	void JumpToAttackMontageSection(int32 NewSection);

	FOnNextAttackCheckDelegate OnNextAttackCheck;
	FOnAttackHitCheckDelegate OnAttackHitCheck;

	
private:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;

	//AttackHitCheck가 애님 노티파이의 이름
	UFUNCTION()
	void AnimNotify_AttackHitCheck();

	UFUNCTION()
	void AnimNotify_NextAttackCheck();

	FName GetAttackMontageSectionName(int32 Section);


	
};
