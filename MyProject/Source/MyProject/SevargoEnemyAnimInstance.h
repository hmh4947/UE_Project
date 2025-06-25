// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyProject.h"
#include "EnemyStateEnum.h"
#include "SevargoEnemyAnimInstance.generated.h"


/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(FOnSwingAttackEndDelegate);
UCLASS()
class MYPROJECT_API USevargoEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	void PlaySwingMontage();

	USevargoEnemyAnimInstance();

	//attack이 끝났는지 확인
	FOnSwingAttackEndDelegate OnSwingAttackEnd;


	UFUNCTION()
	void OnSwingAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void PlayDeathMontage();

	void OnDeath();
	
	UFUNCTION()
	void SetDeathState();
	
	UPROPERTY()
	EnemyState EnemyStateEnum;

private:
	virtual void NativeUpdateAnimation(float DeltaTime) override; //프레임마다 호출

	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly,Category=Attack,Meta=(AllowPrivateAccess=true))
	UAnimMontage* SwingMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* DeathMontage;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category=State, Meta=(AllowPrivateAccess =true))
	bool OnDeathState;

	
	UPROPERTY()
	class USevargoEnemyAnimInstance* ABAnim;

	UPROPERTY(EditAnyWhere)
	class ASevargoEnemy* Enemy;
};
