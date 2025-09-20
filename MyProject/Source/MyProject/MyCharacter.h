// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InteractionInterface.h"
#include "MyCharacter.generated.h"

class AMyProjectHUD;

USTRUCT()
struct FInteractionData
{
	GENERATED_USTRUCT_BODY()
	
	FInteractionData() : CurrentInteractable(nullptr), LastInteractionCheckTime(0.0f)
	{

	};
	UPROPERTY()
	AActor* CurrentInteractable;

	float LastInteractionCheckTime;

};
UCLASS()
class MYPROJECT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	// Sets default values for this character's properties
	AMyCharacter();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FORCEINLINE bool IsInteracting() const { return GetWorldTimerManager().IsTimerActive(TimerHandle_Interaction); };

	UPROPERTY(EditAnyWhere, Category = Input)
	class UInputAction* IA_Interaction;

	virtual void Initialize();
protected:
	UPROPERTY()
	AMyProjectHUD* HUD;
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera",meta=(AllowPrivateAccess="true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Camera",meta=(AllowPrivateAccess="true"))
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category="Character | Interaction")
	TScriptInterface<IInteractionInterface> TargetInteractable;

	//상호작용 빈도
	float InteractionCheckFrequency;

	//상호작용 거리
	float InteractionCheckDistance;

	//상호작용을 위한 타이머
	FTimerHandle TimerHandle_Interaction;

	FInteractionData InteractionData;

	void PeformInteractionCheck();
	void FoundInteractable(AActor* NewInteractable);
	void NoInteractableFound();
	void BeginInteract();
	void EndInteract();
	void Interact();

};
