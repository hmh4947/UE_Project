// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Skill/EnemyUltimateSwingSkill.h"
#include "MyProject/SevargoEnemy.h"
#include "MyProject/Skill/UltimateSwingEffect.h"
void AEnemyUltimateSwingSkill::BeginPlay()
{
	Super::BeginPlay();
	InitObjects();
	ActiveSkill();
}

void AEnemyUltimateSwingSkill::HitCheck_Implementation()
{
	ReuseObjects();
}

void AEnemyUltimateSwingSkill::damageArea(float radius, float damageAmount, FVector startPos, FVector endPos)
{
	
}

void AEnemyUltimateSwingSkill::OnEffectEnd(AUltimateSwingEffect* FinishedEffect)
{
	

	USphereComponent* SphereComponent = Instances->FindComponentByClass<USphereComponent>();
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);


	FTimerHandle TimerHandle;
	FinishedEffect->GetWorldTimerManager().SetTimer(
		TimerHandle,
		[SphereComponent]()
		{
			SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		},
		0.1f,   // 충돌 유지 시간
		false
	);
}

void AEnemyUltimateSwingSkill::InitObjects()
{
	AUltimateSwingEffect* Damage = GetWorld()->SpawnActor<AUltimateSwingEffect>(Instance);

	Damage->SetActorEnableCollision(false);
	Damage->SetActorHiddenInGame(true);
	Damage->setDamage(damage);
	UNiagaraComponent* NiagaraComp = Damage->FindComponentByClass<UNiagaraComponent>();
	if (!NiagaraComp) return;
	// 생성 직후엔 재생 안 되도록
	NiagaraComp->SetAutoActivate(false);
	NiagaraComp->SetAutoDestroy(false);
	USphereComponent* SphereComponent = Damage->FindComponentByClass<USphereComponent>();
	if (!SphereComponent) return;
	SphereComponent->SetActive(false);
	Instances=Damage;
}

void AEnemyUltimateSwingSkill::ReuseObjects()
{
	ASevargoEnemy* Enemy = Cast<ASevargoEnemy>(GetOwner());


	if (!Instances) return;

	FVector spawnVector = Enemy->GetActorLocation() + Enemy->GetActorForwardVector()*400.f;
	FRotator Rotation = Enemy->GetActorForwardVector().Rotation()+FRotator(0.f,-90.f,0.f);

	Instances->SetActorLocation(spawnVector);
	Instances->SetActorRotation(Rotation);

	
	UNiagaraComponent* NiagaraComp = Instances->FindComponentByClass<UNiagaraComponent>();
	if (!NiagaraComp) return;
	USphereComponent* SphereComponent = Instances->FindComponentByClass<USphereComponent>();
	if (!SphereComponent)  return;



	AUltimateSwingEffect* SkillEffect = Cast<AUltimateSwingEffect>(Instances);
	if (!SkillEffect) return;
	//바인딩(나이아가라 끝나는 타이밍)
	SkillEffect->EffectFinished.AddUniqueDynamic(this, &AEnemyUltimateSwingSkill::OnEffectEnd);

	Instances->SetActorHiddenInGame(false);
	NiagaraComp->SetHiddenInGame(false);
	NiagaraComp->DeactivateImmediate();  // 이전 상태 초기화
	NiagaraComp->Activate(true);
	SphereComponent->Activate(true);
	Instances->SetActorEnableCollision(true);


	

}
