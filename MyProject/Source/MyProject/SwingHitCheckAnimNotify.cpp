// Fill out your copyright notice in the Description page of Project Settings.


#include "SwingHitCheckAnimNotify.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MyProject/WarriorCharacter.h"

void USwingHitCheckAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{ 

	Super::Notify(MeshComp, Animation);
	
	GEngine->AddOnScreenDebugMessage(-1, 1.0F, FColor::Red, TEXT("Notify"));

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> IgnoreActors;
	

	TEnumAsByte<EObjectTypeQuery> WorldDynamic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	
	ObjectTypes.Add(WorldDynamic);

	FHitResult Result;
	FName WeaponSocket(TEXT("WeaponHit_Socket"));


	FVector SocketPos = MeshComp->GetSocketLocation(TEXT("WeaponHit_Socket"));

		
		bool bResult = UKismetSystemLibrary::SphereTraceSingleForObjects(
			GetWorld(),
			SocketPos,
			SocketPos,
			150.f,
			ObjectTypes,
			false,
			IgnoreActors,
			EDrawDebugTrace::ForDuration,
			Result,
			true);

		if (bResult == true) {
			if (Result.GetActor())
			{
				
				AWarriorCharacter* Player = Cast<AWarriorCharacter>(Result.GetActor());
				if (Player != nullptr)
				{

				
					UPlayerHealthComponent* PlayerHealthComponent = Player->FindComponentByClass<UPlayerHealthComponent>();
					if (PlayerHealthComponent != nullptr)
					{

						
						PlayerHealthComponent->LoseHealth(100);
						UE_LOG(LogTemp, Warning, TEXT("Hit ActorResult: %s"), *Result.GetActor()->GetName());
						
					}

				}

			}
			
		}
		


}


