// Fill out your copyright notice in the Description page of Project Settings.


#include "SevargoEnemy.h"
#include "ClickMovePlayerController.h"
#include "ABAIController.h"



ASevargoEnemy::ASevargoEnemy()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SphereComponent->SetSphereRadius(130.f);
	SphereComponent->SetupAttachment(GetCapsuleComponent());
	//SphereComponent->OnComponentHit.AddDynamic(this, &ASevargoEnemy::OnHit);
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

}


void ASevargoEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void ASevargoEnemy::OnDeath_Implementation()
{
	if (GetOwner()->Implements<UHealthInterface>()) {
		IHealthInterface::Execute_OnDeath(GetOwner());
	}
}

void ASevargoEnemy::OnTakeDamage_Implementation()
{
	AABAIController* EnemyController = Cast<AABAIController>(GetController());
		
	if (EnemyController != nullptr)
	{
		
		EnemyController->UpdateEnemyHealthPercent(HealthComponent->GetHealthPercent());
	}
}



void ASevargoEnemy::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	/*FString OtherActorName = OtherActor->GetName();
//	UE_LOG(LogTemp, Warning, TEXT("OtherActor Name: %s"), *OtherActorName);
	// 충돌한 물체가 Warrior 캐릭터인 경우
	AWarriorCharacter* Player = Cast<AWarriorCharacter>(OtherActor);
	if (Player != nullptr)
	{
	
		UHealthComponent* PlayerHealthComponent = Player->FindComponentByClass<UHealthComponent>();
		if (PlayerHealthComponent != nullptr)
		{
		
			PlayerHealthComponent->LoseHealth(Damage);
		}
		
	}
	*/
}



