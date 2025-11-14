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
class UUserWidget;
class UGameOverWidget;
class UHUDWidget;
UCLASS()
class MYPROJECT_API AClickMovePlayerController : public APlayerController
{
	GENERATED_BODY()
	

	

public:

	
	
	AClickMovePlayerController();

	void Initialize();
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
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = state, Meta = (AllowPrivateAccess = true))
	bool IsMoving;

	//이동 커서
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	void MoveToMouseCursor();
	void HitDash();
	void Dash();
	void StopDash();
	


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = state)
	bool IsDash;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = location)
	FVector CachedDestination; //마우스 클릭 위치 저장

	//HUDWidget
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UHUDWidget> BP_HUDWidget;

	
	void UpdateHealthPercent(float HealthPercent);
	void UpdateQSkillCoolDown(float Percent, ASkills* Skill);
	void UpdateWSkillCoolDown(float Percent, ASkills* Skill);
	void UpdateESkillCoolDown(float Percent, ASkills* Skill);
	void UpdateRSkillCoolDown(float Percent, ASkills* Skill);
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

	UPROPERTY()
	FVector Direction;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = state)
	FVector characterSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = location)
	FVector dash;

	UFUNCTION(BlueprintCallable)
	void BlockWorldClick(UUserWidget* TargetWidget);

	UFUNCTION(BlueprintCallable)
	void UnBlockWorldClick();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = state)
	bool bClickRightMouse;

	//Input
	void InputRightMouseButtonPressed();

	void InputRightMouseButtonReleased();

	void SetNewDestination(const FVector Destination);


	virtual void PlayerTick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = state)
	bool Dashcool=true;


	UPROPERTY()
	FTimerHandle Timer;

	void coolTimer();
	

private:

	AWarriorCharacter* WarriorCharacterInstance;
	 float FollowTime = 0.f;


public:
	UPROPERTY()
	UHUDWidget* HUDWidget;

	UPROPERTY(EditAnywhere,Category="Widget")
	TSubclassOf<UGameOverWidget> GameOverWidgetClass;

	UGameOverWidget* GameOverWidget;

	

	UFUNCTION()
	void CreateGameOverWidget();
	
};
