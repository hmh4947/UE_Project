// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Skill/UltimateSwingEffect.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h" 
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AUltimateSwingEffect::AUltimateSwingEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	NiagaraComponent->SetupAttachment(RootComponent);
	SphereComponent->SetupAttachment(RootComponent);
	NiagaraComponent->SetWorldRotation(FRotator(0.f, -90.f, 0.f));
	SphereComponent->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	NiagaraComponent->SetAutoActivate(false);

}

void AUltimateSwingEffect::FinishEffect(UNiagaraComponent* Niagara)
{
}

void AUltimateSwingEffect::HandleNiagaraFinished(UNiagaraComponent* Comp)
{
	EffectFinished.Broadcast(this);
	SphereComponent->SetActive(false);
}

// Called when the game starts or when spawned
void AUltimateSwingEffect::BeginPlay()
{
	Super::BeginPlay();
	if (UNiagaraComponent* NiagaraComp = FindComponentByClass<UNiagaraComponent>())
	{
		NiagaraComp->OnSystemFinished.AddDynamic(this, &AUltimateSwingEffect::HandleNiagaraFinished);
	}
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AUltimateSwingEffect::OnBeginOverlap);
}

// Called every frame
void AUltimateSwingEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
/*	DrawDebugSphere(GetWorld(),
		SphereComponent->GetComponentLocation(),
		SphereComponent->GetScaledSphereRadius(),
		12, FColor::Green, false, -1, 0, 2);
		*/
	if (!SphereComponent->IsActive() == true) return;
	FVector Forward = GetActorRightVector();
	FRotator Rotation = FRotator(0.f, 90.f, 0.f);
	AddActorWorldOffset(Forward * speed * DeltaTime, true);

}

void AUltimateSwingEffect::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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
}

float AUltimateSwingEffect::getDamage()
{
	return this->damage;
}

void AUltimateSwingEffect::setDamage(float amount)
{
	this->damage = amount;
}

