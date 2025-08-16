// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Skill/AOESkillNotify.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MyProject/SevargoEnemy.h"
#include "MyProject/Skill/SkillComponent.h"
#include "MyProject/Interface/SkillHitCheckInterface.h"
void UAOESkillNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	AActor* Owner = MeshComp->GetOwner();
	//인터페이스가 정의되었는지 확인하고 실행

	ASevargoEnemy* Enemy = Cast<ASevargoEnemy>(Owner);
	if (!Enemy || !Enemy->SkillComponent->getCurrentSkill()) return;
	AActor* OwnerSkill = Enemy->SkillComponent->getCurrentSkill();
	if (OwnerSkill && OwnerSkill->GetClass()->ImplementsInterface(USkillHitCheckInterface::StaticClass()))
	{

		ISkillHitCheckInterface::Execute_HitCheck(Enemy->SkillComponent->getCurrentSkill());
	}

}
