// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "HealthInterface.h"
#include "HUDWidget.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "HealthComponent.h"
#include "SevargoEnemyAnimInstance.h"
#include "ABAIController.h"
#include "EnemyStateEnum.h"
#include "SevargoEnemy.generated.h"

class USkillComponent;
class UEnemyHealthComponent;
class ACutSceneManager;
UCLASS()

class MYPROJECT_API ASevargoEnemy : public AEnemyCharacter, public IHealthInterface
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;
public:

	ASevargoEnemy();

	virtual void Initialize() override;
	virtual void OnDeath_Implementation() override;

	virtual void OnTakeDamage_Implementation() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UEnemyHealthComponent* EnemyHealthComponent;

	virtual void PostInitializeComponents() override;

	UPROPERTY()
	class USevargoEnemyAnimInstance* ABAnim;

	UPROPERTY(VisibleAnywhere)
	AActor* CurrentSkill;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite,Category="Health")
	float health;

	UFUNCTION(BlueprintCallable, Category="EnemyCharacter")
	void AttackStart();
	UFUNCTION(BlueprintCallable, Category = "EnemyCharacter")
	void AttackEnd();

	// 메쉬에서 무기를 받아오는 변수
	FBodyInstance* Weapon;
	// 무기 위치
	FVector SaveAttackStartPos;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool OnDeath;

	UPROPERTY(EditAnyWhere)
	EnemyState EnemyStateEnum;

	UPROPERTY(EditAnyWhere,BlueprintReadOnly)
	USkillComponent* SkillComponent;

private:
	UPROPERTY()
	class UHUDWidget* HUDWidget;
	
	
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = AttackCollision, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereComponent;


protected:
	class AABAIController* Controller;
	//플레이어에게 입힐 데미지
	UPROPERTY(EditAnywhere,Category=Damage)
	float Damage = 30.f;
};
