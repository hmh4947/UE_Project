// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "HealthInterface.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UHealthComponent::LoseHealth(float  amount)
{
	
}

void UHealthComponent::SetHealth(float  amount)
{
	this->health = amount;
}
void UHealthComponent::SetMaxHealth(float  amount)
{
	this->maxHealth = amount;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


