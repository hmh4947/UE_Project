// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Skill/Skills.h"
#include "MyProject/HUDWidget.h"


// Sets default values
ASkills::ASkills()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ASkills::SkillExecute(ACharacter* Character)
{
	//is_active = true;
	UAnimInstance* AnimInstane = Character->GetMesh()->GetAnimInstance();
	AnimInstane->Montage_Play(SkillMontage);
	
}


float ASkills::GetCoolTime() const
{
	return this->coolTime;
}

bool ASkills::GetIsActiveSkill() const
{
	return is_active;
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

void ASkills::UpdateSkillCool()
{
	
}

void ASkills::StartTimer()
{	
	if(is_active==true)
	{
		is_active = false;
		//GetWorldTimerManager().SetTimer(RemainingTimerHandler, this, &ASkills::UpdateSkillCool, 1.0f, true, 1.0f);
		GetWorldTimerManager().SetTimer(TimerHandler, this, &ASkills::ActiveSkill, 1.0f, true, coolTime);
		
	}

}

float ASkills::GetRemainingTime() const
{
	
	
	float remainingtime = GetWorld()->GetTimerManager().GetTimerRemaining(TimerHandler);
	return remainingtime;
}

UAnimMontage* ASkills::GetSkillMontage() const
{
	
	return this->SkillMontage;
}

void ASkills::ActiveSkill()
{
	is_active=true;

}



void ASkills::SetCoolTime(float time)
{
	this->coolTime = time;
}

// Called every frame
void ASkills::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

