// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Skill/EnemyAOESkill.h"
#include "MyProject/SevargoEnemy.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "MyProject/Skill/EnemyAOEEffect.h"

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


void AEnemyAOESkill::InitObjects()
{
	
	isDamage = false;

	for (int i = 0; i < instanceArraySize; i++)
	{

		AEnemyAOEEffect* DamageAOE = GetWorld()->SpawnActor<AEnemyAOEEffect>(Instance);


		DamageAOE->SetActorHiddenInGame(true);
		DamageAOE->setDamage(damage);
		UNiagaraComponent* NiagaraComp = DamageAOE->FindComponentByClass<UNiagaraComponent>();
		if (!NiagaraComp) return;
		// 생성 직후엔 재생 안 되도록
		NiagaraComp->SetAutoActivate(false);
		NiagaraComp->SetAutoDestroy(false);
		////
		NiagaraComp->Activate(true);
		NiagaraComp->DeactivateImmediate();
		NiagaraComp->ResetSystem();
		////
		USphereComponent* SphereComponent = DamageAOE->FindComponentByClass<USphereComponent>();
		if (!SphereComponent) return;
		Instances.Add(DamageAOE);
	}

}

void AEnemyAOESkill::ReuseObjects()
{
	
	ASevargoEnemy* Enemy = Cast<ASevargoEnemy>(GetOwner());
	if (!Enemy) return;

	float enemyLocationX = Enemy->GetActorLocation().X;
	float enemyLocationY = Enemy->GetActorLocation().Y;

	for (AActor* Obj : Instances)
	{
		if (!Obj) continue;

		float randLocationX = FMath::RandRange(enemyLocationX - 500.f, enemyLocationX + 500.f);
		float randLocationY = FMath::RandRange(enemyLocationY - 500.f, enemyLocationY + 500.f);
		FVector spawnVector = FVector(randLocationX, randLocationY, 0);
		Obj->SetActorLocation(spawnVector);

		UNiagaraComponent* NiagaraComp = Obj->FindComponentByClass<UNiagaraComponent>();
		if (!NiagaraComp) continue;
		USphereComponent* SphereComponent = Obj->FindComponentByClass<USphereComponent>();
		if (!SphereComponent) continue;
		AEnemyAOEEffect* SkillEffect = Cast<AEnemyAOEEffect>(Obj);
		if (!SkillEffect) continue;

		//재생 전 콜리전 비활성화
	
		SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);


		//나이아가라 재시작
	

		SkillEffect->EffectFinished.AddUniqueDynamic(this, &AEnemyAOESkill::OnEffectEnd);
		Obj->SetActorHiddenInGame(false);
		NiagaraComp->DeactivateImmediate();
		NiagaraComp->ResetSystem();
		NiagaraComp->Activate(true);
	}
	
}



void AEnemyAOESkill::OnEffectEnd(AEnemyAOEEffect* FinishedEffect)
{
	
	UE_LOG(LogTemp, Warning, TEXT("OnEffectEnd CALLED for AOE!"));
	for (AActor* Obj : Instances)
	{
		if (!Obj) continue;
		USphereComponent* SphereComponent = Obj->FindComponentByClass<USphereComponent>();
		if (!SphereComponent)  continue;
		SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		SphereComponent->SetGenerateOverlapEvents(true);
	
		FTimerHandle TimerHandle;
		FinishedEffect->GetWorldTimerManager().SetTimer(
			TimerHandle,
			[SphereComponent]()
			{
				SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				//SphereComponent->SetGenerateOverlapEvents(false);
			},
			0.1f,   // 충돌 유지 시간
			false
		);
	}
}


