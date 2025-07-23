// Fill out your copyright notice in the Description page of Project Settings.


#include "WarriorCharacter.h"
#include "WarriorAnimInstance.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Sword.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "ClickMovePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "SevargoEnemy.h"
#include "Sword.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnemyHealthComponent.h"
#include "Skill/SkillComponent.h"





AWarriorCharacter::AWarriorCharacter()
{
	MaxCombo = 2;
	AttackEndComboState();
//	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	PlayerHealthComponent = CreateDefaultSubobject<UPlayerHealthComponent>(TEXT("PlayerHealthComponent"));
	skillComponent = CreateDefaultSubobject<USkillComponent>(TEXT("SkillComponent"));
}

void AWarriorCharacter::OnDeath_Implementation()
{
	if (GetOwner()->Implements<UHealthInterface>()) {
		IHealthInterface::Execute_OnDeath(GetOwner());
	}
}


void AWarriorCharacter::OnTakeDamage_Implementation()
{
	AClickMovePlayerController* PlayerController =
		Cast<AClickMovePlayerController>(GetController());
	if(PlayerController!=nullptr)
	{
		PlayerController->UpdateHealthPercent(PlayerHealthComponent->GetHealthPercent());
	}
}
void AWarriorCharacter::SetIsAttacking(bool isAttacking)
{
	this->IsAttacking = isAttacking;
}
void AWarriorCharacter::losehealth()
{
	if (HitTrace.GetActor())
	{
		ASevargoEnemy* Enemy = Cast<ASevargoEnemy>(HitTrace.GetActor());
		if (Enemy != nullptr)
		{

			
			UEnemyHealthComponent* EnemyHealthComponent = Enemy->FindComponentByClass<UEnemyHealthComponent>();
			if (EnemyHealthComponent != nullptr)
			{

				UE_LOG(LogTemp, Warning, TEXT("Hit ActorResult: %s"), *HitTrace.GetActor()->GetName());

				EnemyHealthComponent->LoseHealth(10);
				
			}

		}

	}

}

void AWarriorCharacter::MeleeTrace()
{
	
	MeleeTraceGetHitActor();
	
	
}
void AWarriorCharacter::MeleeTraceGetHitActor()
{
	//tracehit
	isLoseHealth = false;
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC && !bMeleeBlocked) {


		FCollisionQueryParams TraceParams(FName(TEXT("WeaponTrace")),
			false,
			this);

		TArray<FVector> MeleeTrace;
		FVector MeleeTraceBottom = GetMesh()->GetSocketLocation("StartH");
		FVector MeleeTraceTop = GetMesh()->GetSocketLocation("EndH");
		FVector MeleeVectorDirection = MeleeTraceTop - MeleeTraceBottom;
		float MeleeVectorLength = MeleeVectorDirection.Size();

		MeleeVectorDirection.Normalize();

		MeleeTracePrevious.Push(MeleeTraceBottom);
		MeleeTracePrevious.Push(MeleeTraceTop);

		MeleeTrace.Push(MeleeTraceBottom);
		MeleeTrace.Push(MeleeTraceTop);

		
	
		for (int i = 0; i < MeleeVectorLength; i += 1)
		{

			MeleeTracePrevious.Push(MeleeTraceBottom + MeleeVectorDirection * i);
			MeleeTrace.Push(MeleeTraceBottom + MeleeVectorDirection * i);


		}
		/*배열의 모든 요소 출력
		for (FHitResult& HitResult : HitResults) {
			UE_LOG(LogTemp, Warning, TEXT("Hit Actors: %s"), *HitTrace.GetActor()->GetName());
		}
		*/
		// 각 지점에서 레이 트레이스 수행
		for (int i = 0; i < MeleeTrace.Num() - 1; ++i)
		{
			
			FVector Start = MeleeTrace[i];
			FVector End = MeleeTrace[i + 1];

			
			bHit = GetWorld()->LineTraceSingleByChannel(HitTrace, Start, End, ECC_EngineTraceChannel2, TraceParams);
			if (HitTrace.GetActor())
			{


				ASevargoEnemy* Enemy = Cast<ASevargoEnemy>(HitTrace.GetActor());
				if (Enemy != nullptr)
				{

					UHealthComponent* EnemyHealthComponent = Enemy->FindComponentByClass<UHealthComponent>();
					if (EnemyHealthComponent != nullptr)
					{

						isLoseHealth = true;

					}

				}

			}
		
			
		}
		
		//디버그
		if (MeleeTrace.Num() > 0) {
			for (int i = 0; i < MeleeTrace.Num(); i++) {


				GetWorld()->LineTraceMultiByObjectType(
					HitResults,
					MeleeTracePrevious[i],
					MeleeTrace[i],
					FCollisionObjectQueryParams(ECC_EngineTraceChannel1),
					TraceParams);

				MeleeTracePrevious[i] = MeleeTrace[i];
				if (FHitResult::GetFirstBlockingHit(HitResults)) {


					HitResults.Empty();
					MeleeTracePrevious.Empty();
					bMeleeBlocked = true;
					break;

				}


				DrawDebugLine(
					GetWorld(),
					MeleeTracePrevious[i],
					MeleeTrace[i],
					FColor::Red,
					false,
					0.2f,
					0,
					1.0f
				);


			}

		}

	}
	
}

bool AWarriorCharacter::setAttacking(bool isAttacking)
{
	IsAttacking = isAttacking;
	return IsAttacking;
}



//Warrior Character Input
void AWarriorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))

	{
		EnhancedInputComponent->BindAction(IA_Attack, ETriggerEvent::Triggered, this, &AWarriorCharacter::Attack);
		EnhancedInputComponent->BindAction(IA_KeyboardQ, ETriggerEvent::Completed, this, &AWarriorCharacter::Attack_Q);
		EnhancedInputComponent->BindAction(IA_KeyboardW, ETriggerEvent::Completed, this, &AWarriorCharacter::Attack_W);
		EnhancedInputComponent->BindAction(IA_KeyboardE, ETriggerEvent::Completed, this, &AWarriorCharacter::Attack_E);
		EnhancedInputComponent->BindAction(IA_KeyboardR, ETriggerEvent::Completed, this, &AWarriorCharacter::Attack_R);
	
	}
}

void AWarriorCharacter::BeginPlay()
{
	Super::BeginPlay();
	FName WeaponSocket(TEXT("SwordSocket"));
	auto Weapon = GetWorld()->SpawnActor<ASword>(FVector::ZeroVector, FRotator::ZeroRotator);
	
	if (nullptr != Weapon)
	{
		Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
	}
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC_Warrior_Character, 0);
		}
	}

	
}



void AWarriorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 캐릭터의 현재 위치를 가져옴
	CharacterLocation = GetActorLocation();
	// 캐릭터의 이동 속도

	Speed = GetCharacterMovement()->MaxWalkSpeed;
	CurrentRotator = GetActorRotation();
	
}

void AWarriorCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
	AttackEndComboState();

	UE_LOG(LogTemp, Warning, TEXT("Attack Montage Ended"));
	
}


//새 콤보 시작
void AWarriorCharacter::AttackStartComboState()
{
	CanNextCombo = true;
	IsComboInputOn = false;
	
	//1부터 MaxCombo사이의 값으로 조정
	CurrentCombo = FMath::Clamp<int32>(CurrentCombo + 1, 1, MaxCombo);
	
}

void AWarriorCharacter::AttackEndComboState()
{
	IsComboInputOn = false;
	CanNextCombo = false;
	CurrentCombo = 0;
	
}

//왼쪽 마우스 클릭시 마우스 방향을 바라봄
void AWarriorCharacter::Turn()
{

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		FHitResult Hit;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
		if (Hit.bBlockingHit)
		{

			// 히트 결과에서 히트된 위치를 가져옴
			HitLocation = Hit.ImpactPoint;

			FVector Start = Hit.ImpactPoint;
			FVector End = Start + Hit.Normal * 100.0f;
			DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 5.0f, 0, 1.0f);

			// 캐릭터의 현재 위치를 가져옴
			CharacterLocation = GetActorLocation();

			// 히트 방향을 계산함

			HitDirection = (HitLocation - CharacterLocation).GetSafeNormal2D();

			// 히트 방향으로의 회전 값을 계산함
			FRotator NewRotation = UKismetMathLibrary::MakeRotFromX(HitDirection);
			// 캐릭터의 회전을 설정함
			SetActorRotation(NewRotation);


		}
	}
	
}


void AWarriorCharacter::Attack()
{
	
	CanNextCombo = true;
	
	//1타 공격시
	if(!IsAttacking)
	{
		Turn();
		UE_LOG(LogTemp, Warning, TEXT("first Attack "));
		
		//1타 몽타주 재생
		AttackStartComboState();
		
		ABAnim->PlayAttackMontage();
		ABAnim->JumpToAttackMontageSection(CurrentCombo);
		IsAttacking = true;
	
	
	}
	if (CanNextCombo && IsComboInputOn)
	{
		UE_LOG(LogTemp, Warning, TEXT("second  Attack "));

		ABAnim->JumpToAttackMontageSection(2);
		CanNextCombo = false;
		AttackEndComboState();
	}
}

void AWarriorCharacter::setCurrentSkill(AActor* skill)
{
	CurrentSkill = skill;
}
void AWarriorCharacter::Attack_Q()
{
	if (IsAttacking) return;
	
	skillComponent->Skill(this, ESkillInput::ESI_InputQ);
	setCurrentSkill(skillComponent->getCurrentSkill());

}

void AWarriorCharacter::Attack_W()
{
	if (IsAttacking) return;

	skillComponent->Skill(this, ESkillInput::ESI_InputW);
	setCurrentSkill(skillComponent->getCurrentSkill());
}

void AWarriorCharacter::Attack_E()
{
	if (IsAttacking) return;
	skillComponent->Skill(this, ESkillInput::ESI_InputE);
	setCurrentSkill(skillComponent->getCurrentSkill());
}

void AWarriorCharacter::Attack_R()
{
	if (IsAttacking) return;
	skillComponent->Skill(this, ESkillInput::ESI_InputR);
	setCurrentSkill(skillComponent->getCurrentSkill());
	

}




void AWarriorCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABAnim = Cast<UWarriorAnimInstance>(GetMesh()->GetAnimInstance());

	if (ABAnim)
	{
		ABAnim->OnMontageEnded.AddDynamic(this, &AWarriorCharacter::OnAttackMontageEnded);
		ABAnim->OnNextAttackCheck.AddLambda([this]() -> void {
			UE_LOG(LogTemp, Warning, TEXT("Attack1 Check"));
			CanNextCombo = true;
			IsComboInputOn = true;

			//다음 콤보로 갈 수 없고, 콤보 버튼이 눌렸다면
			if (!CanNextCombo && IsComboInputOn)
			{
				UE_LOG(LogTemp, Warning, TEXT("Attack2 Check"));

			}

		});
	}


}

