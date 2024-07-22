// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "HealthInterface.h"
#include "HUDWidget.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "HealthComponent.h"
#include "SevargoEnemy.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ASevargoEnemy : public AEnemyCharacter, public IHealthInterface
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;
public:

	ASevargoEnemy();

	virtual void OnDeath_Implementation() override;

	virtual void OnTakeDamage_Implementation() override;


	class UHealthComponent* HealthComponent;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit);

private:
	UPROPERTY()
	class UHUDWidget* HUDWidget;

	
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = AttackCollision, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereComponent;

	

protected:
	//플레이어에게 입힐 데미지
	UPROPERTY(EditAnywhere,Category=Damage)
	float Damage = 30.f;
};
