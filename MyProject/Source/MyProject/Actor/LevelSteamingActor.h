// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelSteamingActor.generated.h"
class UBoxComponent;
class UUserWidget;
class UMediaSoundComponent;
class UMediaPlayer;
class UMediaSource;
class UHUDWidget;
class ACharacter;
UCLASS()

class MYPROJECT_API ALevelSteamingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelSteamingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AActor> spawnEnemy;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<UUserWidget> spawnWidget;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category = "Level")
	FName level;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Media")
	UMediaSoundComponent* MediaSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media")
	UMediaPlayer* MediaPlayer;  

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media")
	UMediaSource* MyMediaSource;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UHUDWidget> HUDWidget;


	UFUNCTION()
	virtual void ClosedWidget();

	void SetVisibleEnemyHealthBar();
	UPROPERTY(VisibleAnywhere)
	UUserWidget* LevelStreamingWidget;

	ACharacter* playerCharacter;
};
