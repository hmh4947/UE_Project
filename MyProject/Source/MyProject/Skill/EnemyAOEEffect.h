// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyProject/Interface/SkillHitCheckInterface.h"
#include "EnemyAOEEffect.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
class USphereComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEffectFinished, AEnemyAOEEffect*, Effect);

UCLASS(Blueprintable)
class MYPROJECT_API AEnemyAOEEffect : public AActor, public ISkillHitCheckInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyAOEEffect();
	
	UPROPERTY(BlueprintAssignable)
	FOnEffectFinished EffectFinished;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
	UNiagaraSystem* NiagaraEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UNiagaraComponent* NiagaraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* SphereComponent;


	UFUNCTION()
	void HandleNiagaraFinished(UNiagaraComponent* Comp);

	UFUNCTION()
	void OnBeginOverlap(
		UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool isDamage;
	
public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;


	float getDamage();
	void setDamage(float amount);
private:
	float damage;
};
