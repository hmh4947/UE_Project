// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ESkillInfo.h"
#include "Skills.h"
#include "SkillComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInitActivatableSkill);
class ASkills;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillComponent();

private:
	friend class AWarriorCharacter;
	friend class AABAIController;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Skill(ACharacter* Character, const ESkillInput& SkillInput);
	
	void setCurrentSkill(ASkills* skill);

	ASkills* getCurrentSkill() const;


	const TArray<TObjectPtr<ASkills>>& GetActivatableSkills() const;
	TObjectPtr<ASkills>& GetActivatableSkill(int32 Index);
	UPROPERTY(BlueprintAssignable)
	FInitActivatableSkill InitActivatableSkill;

	
private:
	
	UPROPERTY(VisibleAnywhere)
	ASkills* currentSkill;

	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<ASkills>> ActivatableSkills;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<ASkills>> StartSkillsClass;

	void startSkill(ACharacter* Character, const ESkillInput& SkillInput, ASkills* skill);
};
