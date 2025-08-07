// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Skill/EnemyAOEEffect.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h" 

// Sets default values
AEnemyAOEEffect::AEnemyAOEEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	NiagaraSystem = CreateDefaultSubobject<UNiagaraSystem>(TEXT("NiagaraSystem"));
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetupAttachment(RootComponent);
	NiagaraComponent->SetAutoActivate(false);

}

// Called when the game starts or when spawned
void AEnemyAOEEffect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyAOEEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

