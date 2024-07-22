// Fill out your copyright notice in the Description page of Project Settings.


#include "WarriorAnimInstance.h"

void UWarriorAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	//AnimInstance 기본 함수, 받은 텍스트에 해당하는 섹션을 찾아 실행
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection), AttackMontage);

}

UWarriorAnimInstance::UWarriorAnimInstance()
{

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT("/Game/Ani/PlayerANI/AnimMontage/AM_Attack.AM_Attack"));

	if (ATTACK_MONTAGE.Succeeded())
	{
		AttackMontage = ATTACK_MONTAGE.Object;
	}
}

void UWarriorAnimInstance::PlayAttackMontage()
{
	Montage_Play(AttackMontage, 1.0f);

}
void UWarriorAnimInstance::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast();
}
void UWarriorAnimInstance::AnimNotify_NextAttackCheck()
{
	OnNextAttackCheck.Broadcast();
}
FName UWarriorAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}
