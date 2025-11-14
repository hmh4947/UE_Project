// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class AMyProjectHUD;

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


};
