// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sword.generated.h"

UCLASS()
class MYPROJECT_API ASword : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASword();

	UPROPERTY(EditAnywhere, Category = Weapon)
	USkeletalMeshComponent* Weapon;

	void MeleeTrace();

	UPROPERTY()
	TArray<FVector> MeleeTracePrevious;
	UPROPERTY()
	TArray<FVector> MeleeTraceCurrent;
	UPROPERTY()
	TArray<FHitResult> WallHit;
	bool bMeleeBlocked;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
