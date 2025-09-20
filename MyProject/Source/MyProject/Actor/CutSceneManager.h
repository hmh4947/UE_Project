// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CutSceneManager.generated.h"
class UUserWidget;
class UDialogWidget;
class UMediaSoundComponent;
class UMediaPlayer;
class UMediaSource;
class UHUDWidget;
class ACharacter;
class ASevargoEnemy;
class UDialogNodeAsset;
UENUM(BlueprintType)
enum class ECutSceneType:uint8
{
	None,
	BossStart	UMETA(DisplayName = "BossStart"),
	BossEvent	UMETA(DisplayName = "BossEvent"),
	BossEnd		UMETA(DisplayName = "BossEnd"),
};

UCLASS()
class MYPROJECT_API ACutSceneManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACutSceneManager();


	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Cutscenes")

	TMap<ECutSceneType, UMediaSource*> CutsceneMap;


	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<ASevargoEnemy> spawnEnemy;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<UUserWidget> spawnWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Level")
	FName level;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Media")
	UMediaSoundComponent* MediaSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Media")
	UMediaPlayer* MediaPlayer;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UHUDWidget> HUDWidget;

	UFUNCTION(BlueprintCallable)
	void PlayCutScene(ECutSceneType type);
	
	UFUNCTION(BlueprintCallable)
	void SetMediaPlayerWidget(UUserWidget* widget);

	UPROPERTY(BlueprintReadWrite, Category = "Widget")
	UDialogWidget* Dialog;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Dialog")
	UDialogNodeAsset* eventDialogAsset;
private:
	UFUNCTION()
	void OnStartcutsceneEndReached();

	UFUNCTION()
	void OnEventcutsceneEndReached();

	UFUNCTION()
	void OnEndcutsceneEndReached();

	void ClosedWidget();

	void SetVisibleEnemyHealthBar();

	UPROPERTY(VisibleAnywhere)
	UUserWidget* mediaPlayerWidget;

	ACharacter* playerCharacter;


	



private:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
