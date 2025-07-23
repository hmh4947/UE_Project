// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Skill/Skills.h"
#include "MyProject/HUDWidget.h"

#include "Kismet/KismetSystemLibrary.h"
#include "MyProject/ClickMovePlayerController.h"



#include "DrawDebugHelpers.h"
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
bool ASkills::GetIsLoseHealth() const
{
	return this->isLoseHealth;
}

void ASkills::SetIsLoseHealth(bool islosehealth)
{
	this->isLoseHealth = islosehealth;
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

void ASkills::StartTimer()
{	
	if(is_active==true)
	{
		is_active = false;
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

void ASkills::MeleeTrace()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AClickMovePlayerController* Controller = Cast<AClickMovePlayerController>(PC);

	AWarriorCharacter* Warrior = Cast<AWarriorCharacter>(Controller->GetCharacter());
	if (PC && !bMeleeBlocked) {


		FCollisionQueryParams TraceParams(FName(TEXT("WeaponTrace")), false, Warrior);

		TArray<FVector> MeleeTrace;
		FVector MeleeTraceBottom = Warrior->GetMesh()->GetSocketLocation("StartH");
		FVector MeleeTraceTop = Warrior->GetMesh()->GetSocketLocation("EndH");
		FVector MeleeVectorDirection = MeleeTraceTop - MeleeTraceBottom;
		float MeleeVectorLength = MeleeVectorDirection.Size();

		MeleeVectorDirection.Normalize();

		MeleeTracePrevious.Push(MeleeTraceBottom);
		MeleeTracePrevious.Push(MeleeTraceTop);

		MeleeTrace.Push(MeleeTraceBottom);
		MeleeTrace.Push(MeleeTraceTop);



		for (int i = 0; i < MeleeVectorLength; i += 1)
		{

			MeleeTracePrevious.Push(MeleeTraceBottom + MeleeVectorDirection * i);
			MeleeTrace.Push(MeleeTraceBottom + MeleeVectorDirection * i);


		}

		// 각 지점에서 레이 트레이스 수행
		for (int i = 0; i < MeleeTrace.Num() - 1; ++i)
		{
			FHitResult Hit;
			FVector Start = MeleeTrace[i];
			FVector End = MeleeTrace[i + 1];

			//overlap
			bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_GameTraceChannel7, TraceParams);
			if (!Hit.GetActor()) return;

			UE_LOG(LogTemp, Warning, TEXT("Hit Actors: %s"), *Hit.GetActor()->GetName());

			ASevargoEnemy* Enemy = Cast<ASevargoEnemy>(Hit.GetActor());
			if (!Enemy) return;
			UHealthComponent* EnemyHealthComponent = Enemy->FindComponentByClass<UHealthComponent>();
			if (!HitTrace.GetActor())
			{
				//지점 마다 수행한 트레이스가 충돌했다면 그 정보를 hittrace에 저장
				HitTrace = Hit;
			}
			//	if (!EnemyHealthComponent) return;
			isLoseHealth = true;
			//충돌이 하나라도 되었으면 빠져나옴
			break;



		}

		//디버그
		if (MeleeTrace.Num() > 0) {
			for (int i = 0; i < MeleeTrace.Num(); i++) {


				GetWorld()->LineTraceMultiByObjectType(
					HitResults,
					MeleeTracePrevious[i],
					MeleeTrace[i],
					FCollisionObjectQueryParams(ECC_EngineTraceChannel2),
					TraceParams);

				MeleeTracePrevious[i] = MeleeTrace[i];
				if (FHitResult::GetFirstBlockingHit(HitResults)) {


					HitResults.Empty();
					MeleeTracePrevious.Empty();
					bMeleeBlocked = true;
					break;

				}


				DrawDebugLine(
					GetWorld(),
					MeleeTracePrevious[i],
					MeleeTrace[i],
					FColor::Red,
					false,
					0.2f,
					0,
					1.0f
				);


			}

		}

	}
}

void ASkills::LoseHealth()
{
	if (HitTrace.GetActor())
	{
		ASevargoEnemy* Enemy = Cast<ASevargoEnemy>(HitTrace.GetActor());
		if (Enemy != nullptr)
		{


			UEnemyHealthComponent* EnemyHealthComponent = Enemy->FindComponentByClass<UEnemyHealthComponent>();
			if (EnemyHealthComponent != nullptr)
			{

				UE_LOG(LogTemp, Warning, TEXT("Hit ActorResult: %s"), *HitTrace.GetActor()->GetName());

				EnemyHealthComponent->LoseHealth(damage);

			}

		}

	}
}

// Called every frame
void ASkills::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

