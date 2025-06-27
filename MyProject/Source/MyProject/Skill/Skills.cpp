// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Skill/Skills.h"

// Sets default values
ASkills::ASkills()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ASkills::SkillExecute(ACharacter* Character)
{
	UAnimInstance* AnimInstane = Character->GetMesh()->GetAnimInstance();
	AnimInstane->Montage_Play(SkillMontage);

}

void ASkills::DamageInRadius_Implementation()
{
}

// Called when the game starts or when spawned
void ASkills::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASkills::damageArea(float radius, float damageAmount,FVector startPos,FVector endPos)
{

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> IgnoreActors;



	AWarriorCharacter* Warrior = Cast<AWarriorCharacter>(GetOwner());

	TEnumAsByte<EObjectTypeQuery> WorldDynamic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1);

	ObjectTypes.Add(WorldDynamic);

	FHitResult Result;


	//FVector SocketPos = Warrior->getSwordSocket();


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

			ASevargoEnemy* Enemy = Cast<ASevargoEnemy>(Result.GetActor());
			if (Enemy != nullptr)
			{


				UEnemyHealthComponent* EnemyHealthComponent = Enemy->FindComponentByClass<UEnemyHealthComponent>();
				if (EnemyHealthComponent != nullptr)
				{


					EnemyHealthComponent->LoseHealth(damageAmount);

				}

			}

		}

	}

}

// Called every frame
void ASkills::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

