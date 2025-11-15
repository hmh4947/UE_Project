// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Skill/TrainSkills.h"
#include "MyProject/WarriorCharacter.h"
#include "MyProject/SevargoEnemy.h"
#include "GameFramework/Pawn.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "MyProject/Ai/BTTask_EnemySwingAttack.h"



ESkillType ATrainSkills::GetSkillType() const
{
    return SkillType;
}

bool ATrainSkills::GetIsHit() const
{
    return is_hit;
}

int32 ATrainSkills::getHitCount() const
{
    return hit_count;
}

bool ATrainSkills::GetActiveSkill() const
{
    return is_active;
}



void ATrainSkills::SkillExecute(APawn* Pawn)
{
	
	if (!Pawn) return;

	USkeletalMeshComponent* Mesh = Pawn->FindComponentByClass<USkeletalMeshComponent>();
	if (!Mesh) return;
	
	UAnimInstance* AnimInstance = Mesh->GetAnimInstance();
	if (!AnimInstance) return;
	if (!SkillMontage) return;


	
	AnimInstance->Montage_Play(SkillMontage);
	// Delegate ¿¬°á
	FOnMontageEnded MontageEndDelegate;
	MontageEndDelegate.BindLambda([this](UAnimMontage* Montage, bool bInterrupted)
		{
			OnSkillMontageEnd.ExecuteIfBound(Montage, bInterrupted);
		});

	AnimInstance->Montage_SetEndDelegate(MontageEndDelegate, SkillMontage);
	
}
void ATrainSkills::StartTimer()
{

	if (is_active == true)
	{
		is_active = false;
		GetWorldTimerManager().SetTimer(EnemySkillTimerHandler, this, &ATrainSkills::ActiveSkill, 1.0f, true, coolTime);

	}
}

void ATrainSkills::damageArea(float radius, float damageAmount, FVector startPos, FVector endPos)
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> IgnoreActors;
	ASevargoEnemy* Enemy = Cast<ASevargoEnemy>(GetOwner());
	IgnoreActors.Add(Enemy);


	TEnumAsByte<EObjectTypeQuery> WorldDynamic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1);

	ObjectTypes.Add(WorldDynamic);

	FHitResult Result;


	bool bResult = UKismetSystemLibrary::SphereTraceSingleForObjects(
		GetWorld(),
		startPos,
		endPos,
		radius,
		ObjectTypes,
		false,
		IgnoreActors,
		EDrawDebugTrace::ForDuration,
		Result,
		true);

	if (bResult == true) {
		if (Result.GetActor())
		{
			ACharacter* Character= Cast<ACharacter>(Result.GetActor());
			AWarriorCharacter* WarriorCharacter = Cast<AWarriorCharacter>(Character);
			if (WarriorCharacter != nullptr)
			{


				UHealthComponent* HealthComponent = WarriorCharacter->FindComponentByClass<UHealthComponent>();
				if (HealthComponent != nullptr)
				{


					HealthComponent->LoseHealth(damageAmount);
					this->hit_count += 1;

				}

			}

		}

	}

}

void ATrainSkills::ActiveSkill()
{
	this->is_active = true;
}


