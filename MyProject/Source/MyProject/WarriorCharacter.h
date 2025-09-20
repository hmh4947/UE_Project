// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "MyProject.h"
#include "GameFramework/Character.h"
#include "WarriorAnimInstance.h"
#include "SevargoEnemyAnimInstance.h"
#include "HealthInterface.h"
#include "HealthComponent.h"
#include "PlayerHealthComponent.h"
#include "WarriorCharacter.generated.h"


/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterDied);

class UHUDWidget;
class USkillComponent;

UCLASS()
class MYPROJECT_API AWarriorCharacter : public AMyCharacter, public IHealthInterface
{
	GENERATED_BODY()

	void Attack();
	void Attack_Q();
	void Attack_W();
	void Attack_E();
	void Attack_R();
	void Turn();
	

	
	virtual void PostInitializeComponents() override;

	UPROPERTY(EditAnywhere)
	USkillComponent* skillComponent;

	void setCurrentSkill(AActor* skill);
public:

	AWarriorCharacter();

	virtual void Initialize() override;

	UPROPERTY(BlueprintAssignable)
	FOnCharacterDied OnCharacterDied;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputMappingContext* IMC_Warrior_Character;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Attack;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Dash;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_KeyboardQ;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_KeyboardW;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_KeyboardE;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_KeyboardR;

	UPROPERTY(VisibleAnywhere)
	AActor* CurrentSkill;

	UPROPERTY(EditAnywhere, Category =Health)
	float health;

	FVector StartL;
	FVector EndL;
	FVector Direction;
	//보간 계산 변수
	float Interp;
protected:

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void BeginPlay() override;


public:
	void SetIsAttacking(bool isAttacking);
	void losehealth();

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

	UPROPERTY()
	class USevargoEnemyAnimInstance* ABEnemyAnim;

	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void OnDeath_Implementation() override;

	virtual void OnTakeDamage_Implementation() override;

	//class UHealthComponent* HealthComponent;
	class UPlayerHealthComponent* PlayerHealthComponent;


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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = speed)
	float Speed;

	void MeleeTrace();
	void MeleeTraceGetHitActor();
	TArray<FVector> MeleeTracePrevious;
	TArray<FVector> MeleeTraceCurrent;

	TArray<FHitResult> HitResults;



	bool bMeleeBlocked;
	bool setAttacking(bool isAttacking);

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	bool isDeath;
protected:
	//적에게 입힐 데미지
	

	UPROPERTY(EditAnywhere, Category = Damage)
	float Damage = 100.f;
	FHitResult HitTrace;
	bool bHit;

	
public:
	bool isLoseHealth=false;

};
