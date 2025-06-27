// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Skill/SkillHitCheckAnimNotify.h"
#include "MyProject/Interface/SkillHitCheckInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MyProject/SevargoEnemy.h"
#include "GameFramework/Actor.h"


void USkillHitCheckAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	
	Super::Notify(MeshComp, Animation);
	AActor* Owner = MeshComp->GetOwner();
	//인터페이스가 정의되었는지 확인하고 실행
	
	AWarriorCharacter* Warrior = Cast<AWarriorCharacter>(Owner);
	if (!Warrior||!Warrior->CurrentSkill) return;
	AActor* OwnerSkill = Warrior->CurrentSkill;
	if (OwnerSkill && OwnerSkill->GetClass()->ImplementsInterface(USkillHitCheckInterface::StaticClass()))
	{
		ISkillHitCheckInterface::Execute_HitCheck(Warrior->CurrentSkill);
	}
	
}
