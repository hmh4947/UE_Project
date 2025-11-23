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
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/UserWidget.h"
#include "MyProject/UI/GameOverWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"





AClickMovePlayerController::AClickMovePlayerController()
{
	APawn* MyPawn = GetPawn();
	bShowMouseCursor = true;
	IsMoving = false;
	FollowTime = 0.f;
	Dashcool = false;
	CachedDestination = FVector::ZeroVector;
	if(GetWorld())
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.0F, FColor::Red, TEXT("timer"));
		GetWorld()->GetTimerManager();
		
	}
	static ConstructorHelpers::FClassFinder<UGameOverWidget>GameOver(TEXT("/Game/UI/WBP_GameOver.WBP_GameOver_C"));
	if (GameOver.Succeeded())
	{
		GameOverWidgetClass = GameOver.Class;
	}
	
}

void AClickMovePlayerController::Initialize()
{
	bShowMouseCursor = true;
	IsMoving = false;
	FollowTime = 0.f;
	Dashcool = false;
	
}



void AClickMovePlayerController::BlockWorldClick(UUserWidget* TargetWidget)
{
	if (!TargetWidget) return;

	SetPause(true);
}

void AClickMovePlayerController::UnBlockWorldClick()
{

	SetPause(false);
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
	if (WarriorCharacterInstance)
	{
		WarriorCharacterInstance->OnCharacterDied.AddDynamic(this, &AClickMovePlayerController::CreateGameOverWidget);
	}
}
void AClickMovePlayerController::UpdateHealthPercent(float HealthPercent)
{
	if (HUDWidget != nullptr) {
		HUDWidget->UpdateHealthPercent(HealthPercent);
	}
}

void AClickMovePlayerController::UpdateQSkillCoolDown(float Percent,ASkills* Skill)
{
	if (!HUDWidget) return;
	UE_LOG(LogTemp, Error, (TEXT("%d")), round(Percent));
	HUDWidget->UpdateQSkillPercent(Percent, Skill);
}

void AClickMovePlayerController::UpdateWSkillCoolDown(float Percent, ASkills* Skill)
{
	if (!HUDWidget) return;

	HUDWidget->UpdateWSkillPercent(Percent, Skill);
}

void AClickMovePlayerController::UpdateESkillCoolDown(float Percent, ASkills* Skill)
{
	if (!HUDWidget) return;

	HUDWidget->UpdateESkillPercent(Percent, Skill);
}

void AClickMovePlayerController::UpdateRSkillCoolDown(float Percent, ASkills* Skill)
{
	if (!HUDWidget) return;

	HUDWidget->UpdateRSkillPercent(Percent, Skill);

}
void AClickMovePlayerController::InputRightMouseButtonPressed()
{
	if (WarriorCharacterInstance->isDeath == true) return;
	WarriorCharacterInstance->GetCharacterMovement()->MaxWalkSpeed=600.f;
	IsDash = false;
	//공격중 이동 불가
	if (!WarriorCharacterInstance->IsAttacking)
	{
		//IsMoving = true;
		bClickRightMouse = true;
	}

}

void AClickMovePlayerController::InputRightMouseButtonReleased()
{
	
	bClickRightMouse = false;	
	if(IsValid(FXCursor))
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), FXCursor, CachedDestination, FRotator(0.f, 90.f, 0),
			FVector(0.8f, 0.8f, 0.8f), true, true, ENCPoolMethod::None, true);
		
	}

}

void AClickMovePlayerController::SetNewDestination(const FVector Destination)
{
	if (!WarriorCharacterInstance->IsAttacking)
	{

		//컨트롤러가 소유하고 있는 폰을 MyPawn에 저장
		APawn* const MyPawn = GetPawn();
		if (MyPawn) {
			float const Distance = FVector::Dist(Destination, MyPawn->GetActorLocation());
			if (Distance >100.0f) {

			

				//함수 호출을 통해 목적지로 폰을 이동시킴(모듈추가)
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Destination);
				
			}
			
		}
	
	}

	
	
}





void AClickMovePlayerController::MoveToMouseCursor()
{
	if (WarriorCharacterInstance->isDeath == true) return;
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
			
		//	DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 5.0f, 0, 1.0f);
	

		}
		
	}

	
}

void AClickMovePlayerController::HitDash()
{
	//대쉬 버튼을 누르면서 마우스 이동 불가 처리 
	//대쉬 쿨타임이 없을때

	if (!WarriorCharacterInstance->IsAttacking&&!Dashcool)
	{
		APawn* const MyPawn = GetPawn();
		CharacterLocation = MyPawn->GetActorLocation();
		StartL = CharacterLocation;
		Direction = CurrentRotator.Vector();


		// 히트 방향으로의 회전 값을 계산함

		//캐릭터의 회전값을 이용해 방향 벡터를 얻음
		EndL = StartL + (Direction * 300);




		//히트 결과 값을 받을 변수
		FHitResult HitDash;

		//탐지할 오브젝트 타입들
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		TEnumAsByte<EObjectTypeQuery> WorldStatic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic);
		TEnumAsByte<EObjectTypeQuery> WorldDynamic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic);
		// 첫 번째 오브젝트 타입을 추가
		ObjectTypes.Add(WorldStatic);
		ObjectTypes.Add(WorldDynamic);

		TArray<AActor*> IgnoreActors;
		//ECC_Visibilty 충돌 검출 및 무시할때 사용,false는 여러 충돌 결과 중 하나만 가져오도록 하여 Hit에 저장
		bool Result = UKismetSystemLibrary::LineTraceSingleForObjects(
			GetWorld(),
			StartL,
			EndL,
			ObjectTypes,
			false,
			IgnoreActors,
			EDrawDebugTrace::None, //특정 시간 동안 디버그 라인 표시
			HitDash,
			true //자기자신 무시
		);
	
		if (Result == true) {
			//FVector 
		
			UE_LOG(LogTemp, Warning, (TEXT("CANT DASH")));
		}
		else {
			
			//장애물이 없다면
			IsDash = true;
			Dashcool = true;
			Dash();
			//쿨타임
			GetWorldTimerManager().SetTimer(Timer, this, &AClickMovePlayerController::coolTimer, 2.f, true, 0.f);
		//	DrawDebugLine(GetWorld(), StartL, EndL, FColor::Purple, false, 5.0f, 0, 1.0f);

			
		}
	}
	
}


void AClickMovePlayerController::Dash()
{
	
	Dashcool = true;
	
	APawn* MyPawn = GetPawn();
	ACharacter* MyCharacter = GetCharacter();
//	if (IsDash) {
//		IsMoving = false;
	//	float DashSpeed = 1000.f;
	//	WarriorCharacterInstance->GetCharacterMovement()->MaxWalkSpeed = DashSpeed;
	//	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, EndL);
		{
			WarriorCharacterInstance->LaunchCharacter(UKismetMathLibrary::GetForwardVector(WarriorCharacterInstance->GetActorRotation()) *3000.f,false,false);

		}
	//	DrawDebugLine(GetWorld(), StartL, EndL, FColor::Red, false, 5.0f, 0, 1.0f);
	
//	}

	
}


void AClickMovePlayerController::StopDash()
{
	IsDash = false;
	Dashcool = true;
	
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
			
		
			if (!Dashcool)
			{
				EnhancedInputComponent->BindAction(IA_Dash, ETriggerEvent::Started, this, &AClickMovePlayerController::HitDash);
				EnhancedInputComponent->BindAction(IA_Dash, ETriggerEvent::Completed, this, &AClickMovePlayerController::StopDash);
	
				
			}
			
		
	}

}

void AClickMovePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	ACharacter* MyCharacter = GetCharacter();
	CurrentRotator=WarriorCharacterInstance->CurrentRotator;

	if (!WarriorCharacterInstance->IsAttacking)
	{
		if (bClickRightMouse) {
			MoveToMouseCursor();

		}
	}
	//if (!IsDash)
	{
		characterSpeed = WarriorCharacterInstance->GetVelocity();


		if (characterSpeed != FVector(0, 0, 0))
		{
			IsMoving = true;
		
		}
		else {
		
			IsMoving = false;
			
		}
	}
	
}

void AClickMovePlayerController::coolTimer()
{
	Dashcool = false;
	if (GetWorldTimerManager().IsTimerActive(Timer)) {
	
		//GEngine->AddOnScreenDebugMessage(-1, 1.0F, FColor::Red, TEXT("Active"));
	
	}

	
}

void AClickMovePlayerController::CreateGameOverWidget()
{
	if (!GameOverWidgetClass) return;
	if (GameOverWidget)
	{
		GameOverWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		GameOverWidget = CreateWidget<UGameOverWidget>(GetWorld()->GetFirstPlayerController(), GameOverWidgetClass);
		GameOverWidget->AddToViewport();
	}
	
}






