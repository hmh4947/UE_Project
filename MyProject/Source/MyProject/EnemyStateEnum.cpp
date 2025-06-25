// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyStateEnum.h"

// Sets default values
AEnemyStateEnum::AEnemyStateEnum()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEnemyStateEnum::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyStateEnum::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

