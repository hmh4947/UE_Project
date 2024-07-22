// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "MyProject.h"
#include "GameFramework/Character.h"
#include "WarriorAnimInstance.h"
#include "HealthInterface.h"
#include "HealthComponent.h"
#include "WarriorCharacter.generated.h"


/**
 * 
 */
UCLASS()
class MYPROJECT_API AWarriorCharacter : public AMyCharacter, public IHealthInterface
{
	GENERATED_BODY()

	void Attack();

	void Turn();

	


	virtual void PostInitializeComponents() override;



public:

	AWarriorCharacter();

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputMappingContext* IMC_Warrior_Character;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Attack;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Dash;

	

protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;


public:

	virtual void Tick(float DeltaTime);

	//몽타주 종료 시점 체크
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	//공격 시작 시점의 상태 설정
	void AttackStartComboState();

	//공격 종료 시점의 상태 설정
	void AttackEndComboState();

	//공격 중인지 확인
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsAttacking;

	//다음 단계 콤보 가능 확인
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool CanNextCombo;

	//다음 단계 콤보 입력여부 확인 변수
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsComboInputOn;

	//현재 콤보
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 CurrentCombo;

	//최대 콤보
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 MaxCombo;

	UPROPERTY()
	class UWarriorAnimInstance* ABAnim;

	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void OnDeath_Implementation() override;

	virtual void OnTakeDamage_Implementation() override;

	class UHealthComponent* HealthComponent;



	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category=location)
	FVector MouseLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category=location)
	FRotator CurrentRotator;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = location)
	FVector HitDirection;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = location)
	FVector HitLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = location)
	FVector CharacterLocation;

	void MeleeTrace();
	TArray<FVector> MeleeTracePrevious;
	TArray<FVector> MeleeTraceCurrent;

	TArray<FHitResult> HitResults;
	bool bMeleeBlocked;


private:
		UPROPERTY()
		class UHUDWidget* HUDWidget;
protected:
	//적에게 입힐 데미지

	UPROPERTY(EditAnywhere, Category = Damage)
	float Damage = 30.f;
	FHitResult HitTrace;
	bool bHit;
};
