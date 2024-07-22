// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickMovePlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "MyCharacter.h"
#include "WarriorCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"




AClickMovePlayerController::AClickMovePlayerController()
{
	APawn* MyPawn = GetPawn();
	bShowMouseCursor = true;
	IsMoving = false;
	FollowTime = 0.f;
	CachedDestination = FVector::ZeroVector;

}

void AClickMovePlayerController::UpdateHealthPercent(float HealthPercent)
{
	if (HUDWidget != nullptr) {
		HUDWidget->UpdateHealthPercent(HealthPercent);
	}
}

void AClickMovePlayerController::BeginPlay()
{
	Super::BeginPlay();	

	//BP_HUDWidget 속성 유효 확인
	if (BP_HUDWidget != nullptr) {
		HUDWidget = CreateWidget<UHUDWidget>(this, BP_HUDWidget);
		HUDWidget->AddToViewport();
	}
	IsMoving = false; //초기화
	IsDash = false;
	//게임 시작시 WarriorCharacterInstance 설정
	WarriorCharacterInstance = Cast<AWarriorCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AWarriorCharacter::StaticClass()));


	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	
}

void AClickMovePlayerController::InputRightMouseButtonPressed()
{
	IsDash = false;
	//공격중 이동 불가
	if (!WarriorCharacterInstance->IsAttacking)
	{
		IsMoving = true;
		bClickRightMouse = true;
		
		
	}

}

void AClickMovePlayerController::InputRightMouseButtonReleased()
{

	IsMoving = false;
	bClickRightMouse = false;	
	
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator(0.f, 90.f, 0),
		FVector(0.8f, 0.8f, 0.8f), true, true, ENCPoolMethod::None, true);
	
}

void AClickMovePlayerController::SetNewDestination(const FVector Destination)
{
	if (!WarriorCharacterInstance->IsAttacking)
	
	{
		
		
		//컨트롤러가 소유하고 있는 폰을 MyPawn에 저장
		APawn* const MyPawn = GetPawn();
		if (MyPawn) {
			float const Distance = FVector::Dist(Destination, MyPawn->GetActorLocation());
			if (Distance > 120.0f) {
				
				
			
					//함수 호출을 통해 목적지로 폰을 이동시킴(모듈추가)
					UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Destination);

				

						



			
			}
			if (IsDash) {
				
				MyPawn->SetActorLocation(EndL);
	
				DrawDebugLine(GetWorld(), StartL, EndL, FColor::Red, false, 5.0f, 0, 1.0f);
			}
		}
	
	}
	
	
}



void AClickMovePlayerController::MoveToMouseCursor()
{
	FollowTime += GetWorld()->GetDeltaSeconds();


	if (!WarriorCharacterInstance->IsAttacking)

	{
		FHitResult Hit;
		//ECC_Visibilty 충돌 검출 및 무시할때 사용,false는 여러 충돌 결과 중 하나만 가져오도록 하여 Hit에 저장
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		//Hit.Location 충돌이 처음 감지된 지점
		//Hit.ImpactPoint 충돌한 물체의 표면에 실제로 닿은 지점
		//둘 다 동일한 위치를 가리킴
		if (Hit.bBlockingHit) {
			
			SetNewDestination(Hit.ImpactPoint);
			CachedDestination = Hit.ImpactPoint;
		

			 Start = Hit.ImpactPoint;
			 End = Start + Hit.Normal * 100.0f;
			DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 5.0f, 0, 1.0f);
	

		}
		
	}

	
}


void AClickMovePlayerController::Dash()
{
	IsDash = true;
	APawn* const MyPawn = GetPawn();
	CharacterLocation = MyPawn->GetActorLocation();
	StartL = CharacterLocation;
	CurrentRotator = MyPawn->GetActorRotation();

	FVector Direction = CurrentRotator.Vector();
	// 히트 방향으로의 회전 값을 계산함

	//캐릭터의 회전값을 이용해 방향 벡터를 얻음



	EndL = StartL + (Direction * 300.f);
	SetNewDestination(EndL);
}

void AClickMovePlayerController::DashReleased()
{
	IsDash = false;
}





void AClickMovePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		

		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Started, this, &AClickMovePlayerController::InputRightMouseButtonPressed);
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AClickMovePlayerController::MoveToMouseCursor);
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Completed, this, &AClickMovePlayerController::InputRightMouseButtonReleased);
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Canceled, this, &AClickMovePlayerController::InputRightMouseButtonReleased);
		EnhancedInputComponent->BindAction(IA_Dash, ETriggerEvent::Started, this, &AClickMovePlayerController::Dash);
		EnhancedInputComponent->BindAction(IA_Dash, ETriggerEvent::Completed, this, &AClickMovePlayerController::DashReleased);

	}
		
	
}




void AClickMovePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	APawn* MyPawn = GetPawn();
	if (!WarriorCharacterInstance->IsAttacking)

	{
		if (bClickRightMouse) {
			MoveToMouseCursor();

		}
	}
	 
}




