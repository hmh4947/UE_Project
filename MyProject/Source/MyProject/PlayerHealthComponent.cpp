// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHealthComponent.h"
#include "HealthInterface.h"

UPlayerHealthComponent::UPlayerHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	P_isDeath = false;
}

void UPlayerHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime,TickType,ThisTickFunction);
}

void UPlayerHealthComponent::SetHealth(float health)
{
	PlayerHealth = health;
}

void UPlayerHealthComponent::LoseHealth(float Amount)
{
	PlayerHealth -= Amount;
	if (GetOwner()->Implements<UHealthInterface>()) {
		//인터페이스 안에서 호출해야 하는 함수는 항상 Execute_접두사가 붙는 이름을 가짐
		IHealthInterface::Execute_OnTakeDamage(GetOwner());


		if (PlayerHealth <= 0.f) {
			IHealthInterface::Execute_OnDeath(GetOwner());
			PlayerHealth = 0.f;
			P_isDeath = true;
		}
	}
}
