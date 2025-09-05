// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Actor/LevelSteamingActor.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"

// Sets default values
ALevelSteamingActor::ALevelSteamingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ALevelSteamingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelSteamingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelSteamingActor::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	
	if (OtherActor == PlayerCharacter)
	{
		UGameplayStatics::UnloadStreamLevel(
			this,
			level,
			FLatentActionInfo(),
			false //ºñµ¿±â
		);
		
		//FVector location = FVector(-3240.f, -20.f, 140.f);
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(spawnEnemy);
		UUserWidget* LevelStreamingWidget = CreateWidget<UUserWidget>(GetWorld(), spawnWidget);
		if (LevelStreamingWidget)
		{
			LevelStreamingWidget->AddToViewport();
		}
	}

}

