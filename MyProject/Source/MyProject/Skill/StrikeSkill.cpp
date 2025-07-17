// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Skill/StrikeSkill.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MyProject/WarriorCharacter.h"
#include "MyProject/ClickMovePlayerController.h"
#include "DrawDebugHelpers.h"
AStrikeSkill::AStrikeSkill()
{
}

void AStrikeSkill::BeginPlay()
{
	Super::BeginPlay();
	ActiveSkill();
}

void AStrikeSkill::HitCheck_Implementation()
{
	AWarriorCharacter* Warrior = Cast<AWarriorCharacter>(GetOwner());

	//FVector SocketPos = Warrior->GetMesh()->GetSocketLocation(TEXT("EndH"));
	FVector SocketPos = Warrior->GetActorLocation();
	
	damageArea(200.f, this->damage, SocketPos, SocketPos);

}

void AStrikeSkill::MeleeTrace()
{
	isLoseHealth = false;
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AClickMovePlayerController* Controller = Cast<AClickMovePlayerController>(PC);
	
	AWarriorCharacter* Warrior = Cast<AWarriorCharacter>(Controller->GetCharacter());
	if (PC && !bMeleeBlocked) {


		FCollisionQueryParams TraceParams(FName(TEXT("WeaponTrace")),
			false,
			this);

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
		/*배열의 모든 요소 출력
		for (FHitResult& HitResult : HitResults) {
			UE_LOG(LogTemp, Warning, TEXT("Hit Actors: %s"), *HitTrace.GetActor()->GetName());
		}
		*/
		// 각 지점에서 레이 트레이스 수행
		for (int i = 0; i < MeleeTrace.Num() - 1; ++i)
		{

			FVector Start = MeleeTrace[i];
			FVector End = MeleeTrace[i + 1];


			bHit = GetWorld()->LineTraceSingleByChannel(HitTrace, Start, End, ECC_EngineTraceChannel2, TraceParams);
			if (HitTrace.GetActor())
			{


				ASevargoEnemy* Enemy = Cast<ASevargoEnemy>(HitTrace.GetActor());
				if (Enemy != nullptr)
				{

					UHealthComponent* EnemyHealthComponent = Enemy->FindComponentByClass<UHealthComponent>();
					if (EnemyHealthComponent != nullptr)
					{

						isLoseHealth = true;

					}

				}

			}


		}

		//디버그
		if (MeleeTrace.Num() > 0) {
			for (int i = 0; i < MeleeTrace.Num(); i++) {


				GetWorld()->LineTraceMultiByObjectType(
					HitResults,
					MeleeTracePrevious[i],
					MeleeTrace[i],
					FCollisionObjectQueryParams(ECC_EngineTraceChannel1),
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

void AStrikeSkill::damageArea(float radius,float damageAmount, FVector startPos, FVector endPos)
{
	Super::damageArea(radius, damageAmount,startPos,  endPos);

}

