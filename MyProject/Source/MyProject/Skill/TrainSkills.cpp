// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Skill/TrainSkills.h"
#include "MyProject/WarriorCharacter.h"
#include "MyProject/SevargoEnemy.h"



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

