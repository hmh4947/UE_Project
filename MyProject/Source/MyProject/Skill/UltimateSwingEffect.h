// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyProject/Interface/SkillHitCheckInterface.h"
#include "UltimateSwingEffect.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;
class USphereComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltimateSwingEffectFinished, AUltimateSwingEffect*, Effect);
UCLASS(Blueprintable)
class MYPROJECT_API AUltimateSwingEffect : public AActor,public ISkillHitCheckInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUltimateSwingEffect();

	UPROPERTY(BlueprintAssignable)
	FOnUltimateSwingEffectFinished EffectFinished;

	UFUNCTION()
	void FinishEffect(UNiagaraComponent* Niagara);

	UFUNCTION()
	void HandleNiagaraFinished(UNiagaraComponent* Comp);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* NiagaraSystem;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* NiagaraComponent;

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComponent;

	UFUNCTION()
	void OnBeginOverlap(
		UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);


	float getDamage();
	void setDamage(float amount);

	UPROPERTY(EditAnywhere)
	float speed;

private:
	float damage;
};
