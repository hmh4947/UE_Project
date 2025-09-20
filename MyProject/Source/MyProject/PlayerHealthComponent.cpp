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

void UPlayerHealthComponent::SetMaxHealth(float  amount)
{
	Super::SetMaxHealth(amount);
}



void UPlayerHealthComponent::SetHealth(float amount)
{
	this->health = amount;
}

void UPlayerHealthComponent::LoseHealth(float  amount)
{
	this->health -= amount;
	if (GetOwner()->Implements<UHealthInterface>()) {
		//인터페이스 안에서 호출해야 하는 함수는 항상 Execute_접두사가 붙는 이름을 가짐
		IHealthInterface::Execute_OnTakeDamage(GetOwner());


		if (this->health <= 0.f) {
			IHealthInterface::Execute_OnDeath(GetOwner());
			this->health = 0.f;
			P_isDeath = true;
		}
	}
}
