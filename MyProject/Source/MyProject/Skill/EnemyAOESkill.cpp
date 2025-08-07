// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Skill/EnemyAOESkill.h"
#include "MyProject/SevargoEnemy.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"

void AEnemyAOESkill::BeginPlay()
{
	Super::BeginPlay();
	InitObjects();
	ActiveSkill();
}

void AEnemyAOESkill::HitCheck_Implementation()
{

	ReuseObjects();
	
}

void AEnemyAOESkill::damageArea(float radius, float damageAmount, FVector startPos, FVector endPos)
{

}

void AEnemyAOESkill::OnDamage(USphereComponent* sphereComponent)
{
	TArray<AActor*> OverlappedActors;
	sphereComponent->GetOverlappingActors(OverlappedActors, AWarriorCharacter::StaticClass());
	for (AActor* OverlappedActor : OverlappedActors)
	{
		AWarriorCharacter* Warrior = Cast<AWarriorCharacter>(OverlappedActor);
		if (Warrior)
		{

			UHealthComponent* HealthComponent = Warrior->FindComponentByClass<UHealthComponent>();
			if (HealthComponent != nullptr)
			{


				HealthComponent->LoseHealth(this->damage);
				isDamage = true;
				
				
			}
		}
	}
	if (isDamage)
	{
		this->hit_count += 1;
	}
}

void AEnemyAOESkill::InitObjects()
{
	isDamage = false;
	
	for (int i = 0; i < instanceArraySize; i++)
	{
		
	
		AActor* DamageAOE = GetWorld()->SpawnActor<AActor>(Instance);
	
		DamageAOE->SetActorEnableCollision(false);
		DamageAOE->SetActorHiddenInGame(true);

		UNiagaraComponent* NiagaraComp = DamageAOE->FindComponentByClass<UNiagaraComponent>();
		if (!NiagaraComp) return;
		// 생성 직후엔 재생 안 되도록
		NiagaraComp->SetAutoActivate(false);

		USphereComponent* SphereComponent = DamageAOE->FindComponentByClass<USphereComponent>();
		if (!SphereComponent) return;
		SphereComponent->SetActive(false);
		Instances.Add(DamageAOE);
	}
}

void AEnemyAOESkill::ReuseObjects()
{
	ASevargoEnemy* Enemy = Cast<ASevargoEnemy>(GetOwner());
	
	float enemyLocationX = Enemy->GetActorLocation().X;
	float enemyLocationY = Enemy->GetActorLocation().Y;
	for(AActor* Obj:Instances)
	{
		if (!Obj) continue;
		
		float randLocationX=FMath::RandRange(enemyLocationX +(-500.f), enemyLocationX+500.f);
		float randLocationY = FMath::RandRange(enemyLocationY + (-500.f), enemyLocationY+ 500.f);
		FVector spawnVector = FVector(randLocationX, randLocationY, 0);
		Obj->SetActorLocation(spawnVector);
		

		UNiagaraComponent* NiagaraComp = Obj->FindComponentByClass<UNiagaraComponent>();
		if (!NiagaraComp) return;
		USphereComponent* SphereComponent = Obj->FindComponentByClass<USphereComponent>();
		if (!SphereComponent) return;
		OnDamage(SphereComponent);

		NiagaraComp->ResetSystem();
		NiagaraComp->Activate(true);

		Obj->SetActorEnableCollision(true);
		Obj->SetActorHiddenInGame(false); 
	}

}

void AEnemyAOESkill::ResetObjects()
{
	for(AActor* Obj:Instances)
	{
		if (!Obj) continue;
		Obj->SetActorEnableCollision(false);
		Obj->SetActorHiddenInGame(true);
		
	}
}
