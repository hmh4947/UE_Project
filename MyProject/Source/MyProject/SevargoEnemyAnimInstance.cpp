// Fill out your copyright notice in the Description page of Project Settings.


#include "SevargoEnemyAnimInstance.h"
#include "SevargoEnemy.h"
#include "HealthComponent.h"
#include "DrawDebugHelpers.h"
#include "EnemyHealthComponent.h"
USevargoEnemyAnimInstance::USevargoEnemyAnimInstance()
{
	OnDeathState = false;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SWING_MONTAGE(TEXT("'/Game/Ani/EnemyANI/AnimMontage/AM_Enemy_Swing.AM_Enemy_Swing'"));
	if (SWING_MONTAGE.Succeeded())
	{
		SwingMontage = SWING_MONTAGE.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DEATH_MONTAGE(TEXT("'/Game/Ani/EnemyANI/AnimMontage/AM_Enemy_Death.AM_Enemy_Death'"));
	if (DEATH_MONTAGE.Succeeded())
	{
		DeathMontage = DEATH_MONTAGE.Object;
	}

}

void USevargoEnemyAnimInstance::PlaySwingMontage()
{
	
	
	UE_LOG(LogTemp, Warning, TEXT("PlaySwingMontage"));
	Montage_Play(SwingMontage, 1.0f);


	
}

void USevargoEnemyAnimInstance::OnSwingAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	OnSwingAttackEnd.Broadcast();
}

void USevargoEnemyAnimInstance::PlayDeathMontage()
{
	
	{
	//	if (!Montage_IsPlaying(DeathMontage))
		{
			UE_LOG(LogTemp, Warning, TEXT("OnDeathMontage"));
			Montage_Play(DeathMontage, 1.0f);
		}
	}
}
		
	


void USevargoEnemyAnimInstance::OnDeath()
{
	auto pawn = TryGetPawnOwner();
	if (IsValid(pawn))
	{
		auto health = Cast<UEnemyHealthComponent>(pawn);
		health->LoseHealth(0);
		PlayDeathMontage();
		UE_LOG(LogTemp, Warning, TEXT("OnDeath"));
	}
}

void USevargoEnemyAnimInstance::SetDeathState()
{
	Enemy = Cast<ASevargoEnemy>(TryGetPawnOwner());
	OnDeathState = Enemy->OnDeath;
}



//enemy 현재 체력을 가져옴
void USevargoEnemyAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	
	Super::NativeUpdateAnimation(DeltaTime);

	
}
