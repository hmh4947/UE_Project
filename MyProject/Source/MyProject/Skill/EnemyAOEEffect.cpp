// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Skill/EnemyAOEEffect.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h" 
#include "Components/SphereComponent.h"
// Sets default values
AEnemyAOEEffect::AEnemyAOEEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	NiagaraSystem = CreateDefaultSubobject<UNiagaraSystem>(TEXT("NiagaraSystem"));
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	
	NiagaraComponent->SetupAttachment(RootComponent);
	SphereComponent->SetupAttachment(NiagaraComponent);
	NiagaraComponent->SetAutoActivate(false);

}


void AEnemyAOEEffect::FinishEffect(UNiagaraComponent* Niagara)
{
	//UE_LOG(LogTemp, Log, TEXT("Niagara System Finished"));
	//SphereComponent->SetActive(true);

}

void AEnemyAOEEffect::HandleNiagaraFinished(UNiagaraComponent* Comp)
{
	EffectFinished.Broadcast(this);
}

void AEnemyAOEEffect::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AWarriorCharacter* Warrior = Cast<AWarriorCharacter>(OtherActor);
	if (Warrior)
	{

		UHealthComponent* HealthComponent = Warrior->FindComponentByClass<UHealthComponent>();
		if (HealthComponent != nullptr)
		{


			HealthComponent->LoseHealth(this->damage);
			//isDamage = true;


		}
	}
	if (isDamage)
	{
			//this->hit_count += 1;
	}
}


// Called when the game starts or when spawned
void AEnemyAOEEffect::BeginPlay()
{
	Super::BeginPlay();
	if (UNiagaraComponent* NiagaraComp = FindComponentByClass<UNiagaraComponent>())
	{
		NiagaraComp->OnSystemFinished.AddUniqueDynamic(this, &AEnemyAOEEffect::HandleNiagaraFinished);
	}
	SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AEnemyAOEEffect::OnBeginOverlap);
}


// Called every frame
void AEnemyAOEEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AEnemyAOEEffect::getDamage()
{
	return this->damage;
}

void AEnemyAOEEffect::setDamage(float amount)
{
	this->damage = amount;
}

