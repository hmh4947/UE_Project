// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Skills.generated.h"

UCLASS()
class MYPROJECT_API ASkills : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkills();

	void SkillExecute(ACharacter* Character);

	UPROPERTY(EditDefaultsOnly)
	ESkillName SkillName;

	UPROPERTY(EditDefaultsOnly)
	ESkillInput SkillInput;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DamageInRadius();

	virtual void DamageInRadius_Implementation();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UAnimMontage> SkillMontage;

	UPROPERTY(EditDefaultsOnly)
	float coolTime;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
