// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Skill/EnemyAOEEffect.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h" 
#include "Components/SphereComponent.h"
// Sets default values
AEnemyAOEEffect::AEnemyAOEEffect()
{
	PrimaryActorTick.bCanEverTick = false;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// SphereComponent → Root에 붙임
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);

	// Niagara → SphereComponent 아래로 붙임
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetupAttachment(SphereComponent);
	NiagaraComponent->SetAutoActivate(false);

	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetGenerateOverlapEvents(true);
	SphereComponent->SetCollisionObjectType(ECC_WorldDynamic);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	SphereComponent->InitSphereRadius(116.f);
}
// Called when the game starts or when spawned
void AEnemyAOEEffect::BeginPlay()
{
	Super::BeginPlay();

	UNiagaraComponent* NiagaraComp = FindComponentByClass<UNiagaraComponent>();
	if (!IsValid(NiagaraComp))
	{
		UE_LOG(LogTemp, Error, TEXT("AEnemyAOEEffect: NiagaraComponent not found!"));
		return;
	}

	// 블루프린트 변수(NiagaraEffect) 대신, 경로 문자열을 사용하여 애셋을 런타임에 로드합니다.
	if (!IsValid(NiagaraComp->GetAsset()) && !NiagaraEffectPath.IsEmpty())
	{
		// StaticLoadObject를 사용하여 런타임에 애셋을 로드합니다.
		UNiagaraSystem* LoadedSystem = Cast<UNiagaraSystem>(StaticLoadObject(UNiagaraSystem::StaticClass(), nullptr, *NiagaraEffectPath));

		if (IsValid(LoadedSystem))
		{
			NiagaraComp->SetAsset(LoadedSystem);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("AEnemyAOEEffect: Failed to load Niagara System at path: %s"), *NiagaraEffectPath);
		}
	}

	NiagaraComp->OnSystemFinished.AddUniqueDynamic(this, &AEnemyAOEEffect::HandleNiagaraFinished);

	SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AEnemyAOEEffect::OnBeginOverlap);
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

