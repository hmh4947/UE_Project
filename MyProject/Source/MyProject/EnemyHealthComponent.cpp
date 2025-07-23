// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyHealthComponent.h"
#include "HealthInterface.h"

UEnemyHealthComponent::UEnemyHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	ABAnim = false;
	SetHealth(Health);
}

void UEnemyHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UEnemyHealthComponent::LoseHealth(float Amount)
{
	Health -= Amount;
	//소유자(Player)가 HealthInterface를 구현했다면
	if (GetOwner()->Implements<UHealthInterface>()) {
		//인터페이스 안에서 호출해야 하는 함수는 항상 Execute_접두사가 붙는 이름을 가짐
		IHealthInterface::Execute_OnTakeDamage(GetOwner());

		if (Health <= 0.f) {
			Health = 0.f;
		
			IHealthInterface::Execute_OnDeath(GetOwner());
			
		}
	}
	

}
