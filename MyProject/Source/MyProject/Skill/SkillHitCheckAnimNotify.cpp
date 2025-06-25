// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Skill/SkillHitCheckAnimNotify.h"
#include "MyProject/Interface/SkillHitCheckInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MyProject/SevargoEnemy.h"

void USkillHitCheckAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);


	GEngine->AddOnScreenDebugMessage(-1, 1.0F, FColor::Red, TEXT("Notify"));

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> IgnoreActors;


	TEnumAsByte<EObjectTypeQuery> WorldDynamic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1);

	ObjectTypes.Add(WorldDynamic);

	FHitResult Result;
	FName WeaponSocket(TEXT("SwordSocket"));


	FVector SocketPos = MeshComp->GetSocketLocation(TEXT("EndH"));


	bool bResult = UKismetSystemLibrary::SphereTraceSingleForObjects(
		GetWorld(),
		SocketPos,
		SocketPos,
		1000.f,
		ObjectTypes,
		false,
		IgnoreActors,
		EDrawDebugTrace::ForDuration,
		Result,
		true);

	if (bResult == true) {
		if (Result.GetActor())
		{

			ASevargoEnemy* Enemy = Cast<ASevargoEnemy>(Result.GetActor());
			if (Enemy != nullptr)
			{


				UEnemyHealthComponent* EnemyHealthComponent = Enemy->FindComponentByClass<UEnemyHealthComponent>();
				if (EnemyHealthComponent != nullptr)
				{


					EnemyHealthComponent->LoseHealth(100);
				
				}

			}

		}

	}


}
