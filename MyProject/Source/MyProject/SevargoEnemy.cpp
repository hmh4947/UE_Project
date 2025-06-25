// Fill out your copyright notice in the Description page of Project Settings.


#include "SevargoEnemy.h"
#include "ClickMovePlayerController.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Actor.h"



ASevargoEnemy::ASevargoEnemy()
{
	//폰이 AI에 의해 컨트롤될 때 기본으로 사용할 AI 컨트롤러 클래스
	AIControllerClass = AABAIController::StaticClass();
	//AI 빙의 시기
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SphereComponent->SetSphereRadius(130.f);
	SphereComponent->SetupAttachment(GetCapsuleComponent());
	EnemyHealthComponent = CreateDefaultSubobject<UEnemyHealthComponent>(TEXT("EnemyHealthComponent"));
	OnDeath = false;
}


void ASevargoEnemy::BeginPlay()
{
	Super::BeginPlay();
	this->Weapon = GetMesh()->GetBodyInstance("Weapon_01");

}

void ASevargoEnemy::OnDeath_Implementation()
{
	//if (GetOwner()->Implements<UHealthInterface>()) 
	{
	//	IHealthInterface::Execute_OnDeath(GetOwner());
			//몬스터 상태 변경
		EnemyStateEnum = EnemyState::Dead;
		OnDeath = true;
		ABAnim->SetDeathState();
		ABAnim->PlayDeathMontage();
		//AI 컨트롤러 빙의 해제
		AutoPossessAI = EAutoPossessAI::Disabled;
		UE_LOG(LogTemp, Warning, TEXT("Death_Implementation"));
	}
}

void ASevargoEnemy::OnTakeDamage_Implementation()
{

	AABAIController* EnemyController = Cast<AABAIController>(GetController());
	if (EnemyController != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("OnTakeDamage"));
		EnemyController->UpdateEnemyHealthPercent(EnemyHealthComponent->GetHealthPercent());
		
	}
	
}

void ASevargoEnemy::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABAnim = Cast<USevargoEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	
}


void ASevargoEnemy::AttackStart()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0F, FColor::Red, TEXT("AttackStart"));
	FTransform T = this->Weapon->GetUnrealWorldTransform();
	this->SaveAttackStartPos = T.GetLocation();

}

void ASevargoEnemy::AttackEnd()
{
	FTransform T = this->Weapon->GetUnrealWorldTransform();
	TArray <struct FHitResult> OutOverlaps;

	GetWorld()->SweepMultiByProfile(
		OutOverlaps,
		this->SaveAttackStartPos,
		T.GetLocation(),
		T.GetRotation(),
		FName(TEXT("Pawn")),
		FCollisionShape::MakeSphere(50.0f));


	for (const FHitResult& e : OutOverlaps)
	{
		UE_LOG(LogTemp, Warning, TEXT("Collision !!!!!!!!!!!!!!!!!!!!!  %s"),
			*e.GetActor()->GetFullName(),
			*e.GetComponent()->GetFullName());
	}


	UE_LOG(LogTemp, Warning, TEXT("AttackEnd !!!!!!!!!!!!!!!!!!!!!  %f %f %f"),
		T.GetLocation().X,
		T.GetLocation().Y,
		T.GetLocation().Z);


	DrawDebugLine(GetWorld(), this->SaveAttackStartPos, T.GetLocation(), FColor::Emerald, true, -1, 0, 10);

}









