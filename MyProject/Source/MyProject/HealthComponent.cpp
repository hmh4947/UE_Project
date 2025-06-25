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

void UHealthComponent::LoseHealth(float Amount)
{
	/*

	Health -= Amount;
	
	if (GetOwner()->Implements<UHealthInterface>()) {
		//인터페이스 안에서 호출해야 하는 함수는 항상 Execute_접두사가 붙는 이름을 가짐
		IHealthInterface::Execute_OnTakeDamage(GetOwner());
		
	
	}
	*/
}

void UHealthComponent::SetHealth(float health)
{
	//Health = health;
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

