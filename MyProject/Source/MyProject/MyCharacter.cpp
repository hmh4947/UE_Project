// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "EnhancedInputComponent.h"
#include "MyProjectHUD.h"



// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Begin함수 동작한 직후 Tick 함수가 계속 동작하도록 만듦
	PrimaryActorTick.bStartWithTickEnabled = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	//카메라 회전시 캐릭터가 회전하지 않도록 고정
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//캐릭터 이동방향으로 카메라 회전
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f);

	//캐릭터가 특정 평면에서만 이동하도록 제한
	GetCharacterMovement()->bConstrainToPlane = true;

	//평면을 벗어난 상태시 초기위치를 지정된 평면에 자동으로 정렬
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	//스프링 암이 절대 회전 값을 사용
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	SpringArmComponent->TargetArmLength = 800.0f;
	SpringArmComponent->SetRelativeRotation(FRotator(-60.0f, 45.0f, 0.0f));

	//카메라가 벽을 뚫지 못함,벽에 닿을 시 캐릭터와의 간격을 좁힘
	SpringArmComponent->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	//캐릭터 회전시 카메라가 회전하지 않도록 고정
	CameraComponent->bUsePawnControlRotation = false;

	InteractionCheckFrequency = 0.1;
	InteractionCheckDistance = 200.0f;
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(IA_Interaction, ETriggerEvent::Triggered, this, &AMyCharacter::BeginInteract);
		EnhancedInputComponent->BindAction(IA_Interaction, ETriggerEvent::Completed, this, &AMyCharacter::EndInteract);

	}
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	HUD = Cast<AMyProjectHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	
	
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetWorld()->TimeSince(InteractionData.LastInteractionCheckTime) > InteractionCheckFrequency)
	{
		PeformInteractionCheck();
	}
}

void AMyCharacter::PeformInteractionCheck()
{
	//현재 세계시간을 초로 가져옴
	InteractionData.LastInteractionCheckTime = GetWorld()->GetTimeSeconds();
	
	FVector TraceStart= GetActorLocation()-FVector(0,0,60);
	FVector TraceEnd= TraceStart + (GetActorRotation().Vector() * InteractionCheckDistance);
	FVector TraceRot = GetActorForwardVector() * InteractionCheckDistance;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceRot).ToQuat();
	
	DrawDebugSphere(GetWorld(), TraceStart, InteractionCheckDistance, 10.0f,  FColor::Purple, false, 1.0f, 0, 2.0f);
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	FHitResult TraceHit;
	
	if (GetWorld()->SweepSingleByChannel(TraceHit, TraceStart, TraceEnd, CapsuleRot,ECC_Visibility,FCollisionShape::MakeSphere(10.0f), QueryParams))
	{ 
		
		if (TraceHit.GetActor()->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
		{
			const float Distance = (TraceStart - TraceHit.ImpactPoint).Size();
			if (TraceHit.GetActor() != InteractionData.CurrentInteractable&& Distance<=InteractionCheckDistance)
			{

				FoundInteractable(TraceHit.GetActor());
				return;

			}
			if (TraceHit.GetActor() == InteractionData.CurrentInteractable)
			{
				
				return;
			}
		}
	}
	NoInteractableFound();
}

void AMyCharacter::FoundInteractable(AActor* NewInteractable)
{
	if (IsInteracting())
	{
		EndInteract();
	}

	if (InteractionData.CurrentInteractable)
	{
		//새로운 것이 있는경우 이전 상호 작용 종료
		TargetInteractable = InteractionData.CurrentInteractable;
		TargetInteractable->EndFocus();

	}
	InteractionData.CurrentInteractable = NewInteractable;
	TargetInteractable = NewInteractable;

	HUD->UpdateInteractionWidget(&TargetInteractable->InteractableData);
	TargetInteractable->BeginFocus();
}

void AMyCharacter::NoInteractableFound()
{
	if (IsInteracting())
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);
	}
	//상호작용 가능 항목 유효
	if (InteractionData.CurrentInteractable)
	{
		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->EndFocus();
		}

		HUD->HideInteractionWidget();

		//상호작용 위젯 숨김
		InteractionData.CurrentInteractable = nullptr;
		TargetInteractable = nullptr;
	}
}

void AMyCharacter::BeginInteract()
{
	//상호작용 가능 상태에(변경되지 않음)
	PeformInteractionCheck();

	if (InteractionData.CurrentInteractable)
	{
		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->BeginInteract();
			//상호작용 데이터 확인
			if (FMath::IsNearlyZero(TargetInteractable->InteractableData.InteractionDuration,0.1f))
			{
				Interact();

			}
			else{
				GetWorldTimerManager().SetTimer(TimerHandle_Interaction,
					this,
					&AMyCharacter::Interact,
					TargetInteractable->InteractableData.InteractionDuration,
					false);
					
			}
		}
	}
}

void AMyCharacter::EndInteract()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);
	if (IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->EndInteract();
	}
}

void AMyCharacter::Interact()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);
	if (IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->Interact(this);
	}
}



