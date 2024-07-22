// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "WarriorCharacter.h"
#include "HUDWidget.h"
#include "ClickMovePlayerController.generated.h"


/**
 * 
 */
class UNiagaraSystem;

UCLASS()
class MYPROJECT_API AClickMovePlayerController : public APlayerController
{
	GENERATED_BODY()
	

	

public:

	
	
	AClickMovePlayerController();


	UPROPERTY(EditAnywhere, Category = Input)
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Move;
	
	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* IA_Dash; 


	virtual void SetupInputComponent() override;

	UPROPERTY(BlueprintReadWrite, Category = "Gameplay")
	bool IsAttacking;

	//움직이고 있는 상태인지 체크
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsMoving;

	//이동 커서
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	void MoveToMouseCursor();

	void Dash();
	void DashReleased();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = location)
	bool IsDash;



	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = location)
	FVector CachedDestination; //마우스 클릭 위치 저장

	//HUDWidget
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UHUDWidget> BP_HUDWidget;

	void UpdateHealthPercent(float HealthPercent);

	FVector Start;

	FVector End;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = location)
	FVector StartL;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = location)
	FVector EndL;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = location)
	FRotator CurrentRotator;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = location)
	FVector CharacterLocation;
protected:

	virtual void BeginPlay() override;

	bool bClickRightMouse;

	//Input
	void InputRightMouseButtonPressed();

	void InputRightMouseButtonReleased();

	void SetNewDestination(const FVector Destination);


	virtual void PlayerTick(float DeltaTime) override;

private:

	AWarriorCharacter* WarriorCharacterInstance;
	 float FollowTime = 0.f;
public:
	UPROPERTY()
	class UHUDWidget* HUDWidget;
};
