// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryTest.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "UObject/GarbageCollection.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MyProject/Actor/MyActor.h"
// Sets default values
AMemoryTest::AMemoryTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMemoryTest::BeginPlay()
{
	Super::BeginPlay();
    Initialize();
    StartSpawnLoop();
    GetWorldTimerManager().SetTimer(QuitTimerHandle, this, &AMemoryTest::QuitGame, 100.0f, false);

}
void AMemoryTest::QuitGame()
{
    UWorld* World = GetWorld();
    if (!World) return;

    APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
    if (PC)
    {
        UKismetSystemLibrary::QuitGame(World, PC, EQuitPreference::Quit, true);
    }

}
//메모리 누수
void AMemoryTest::SpawnActors()
{
   // for (int i = 0; i < 10000; i++)
    {
        // 액터를 월드에 스폰 (GC 추적은 되지만, 우리가 직접 참조는 raw pointer에 저장)
        FVector SpawnLocation = FVector(0, 0, 100); // 위치 다르게
        FRotator SpawnRotation = FRotator::ZeroRotator;
        FActorSpawnParameters Params;

        AMyActor* LeakedActor = GetWorld()->SpawnActor<AMyActor>(MyActorClass, SpawnLocation,
            SpawnRotation,
            Params);

        // Raw pointer 배열에만 저장 (UPROPERTY가 아님 → GC 추적 불가)
        RawActorArray.Add(LeakedActor);
    }
    ElapsedTime += SpawnInterval;
    if (ElapsedTime >= SpawnDuration)
    {
        StopSpawnLoop();
    }
}
void AMemoryTest::StartSpawnLoop()
{ 
    ElapsedTime = 0.0f;
   
    // 0.1초마다 SpawnActors 실행
    GetWorldTimerManager().SetTimer(
        SpawnTimerHandle,
        this,
        &AMemoryTest::SpawnActors,
        SpawnInterval,
        true  // 반복 여부
    );
    
 
    //풀링 사용
  /* GetWorldTimerManager().SetTimer(
        SpawnLoopTimerHandle,
        this,
        &AMemoryTest::SpawnFromPool,
        SpawnInterval,
        true
    ); 
   */ 
}
void AMemoryTest::StopSpawnLoop()
{
    //스폰
    GetWorldTimerManager().ClearTimer(SpawnTimerHandle);

    //풀링사용
   // GetWorldTimerManager().ClearTimer(SpawnLoopTimerHandle);

    CollectGarbage(GARBAGE_COLLECTION_KEEPFLAGS);
}
// Called every frame
void AMemoryTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMemoryTest::Initialize()
{
    FVector SpawnLocation = FVector(0, 0, 100);
    FRotator SpawnRotation = FRotator::ZeroRotator;
    FActorSpawnParameters Params;
    for (int i = 0; i < poolSize; i++)
    {
        AMyActor* Actor=GetWorld()->SpawnActor<AMyActor>(MyActorClass, SpawnLocation,  SpawnRotation,
            Params);
        if (Actor)
        {
            Actor->SetActorHiddenInGame(true);
            Actor->SetActorEnableCollision(false);
            ActorPool.Add(Actor);
        }
   }
}

void AMemoryTest::SpawnFromPool()
{
    ElapsedTime += SpawnInterval;
    if (ElapsedTime >= SpawnDuration)
    {
        StopSpawnLoop();
        return;
    }
    AMyActor* Actor = ReSpawn();
    if (Actor)
    {
        // 0.1초 뒤에 ReturnToPool 호출
        FTimerHandle ReturnTimerHandle;
        GetWorld()->GetTimerManager().SetTimer(
            ReturnTimerHandle,
            FTimerDelegate::CreateUObject(this, &AMemoryTest::ReturnToPool, Actor),
            0.1f,
            false
        );
    }
}

void AMemoryTest::ReturnToPool(AMyActor* Actor)
{
    Return(Actor);
}
AMyActor* AMemoryTest::ReSpawn()
{
    for (AMyActor* Actor : ActorPool)
    {
        if (Actor && Actor->IsHidden())
        {
            Actor->SetActorHiddenInGame(false);
            Actor->SetActorEnableCollision(true);
            return Actor;
        }

    }
    return nullptr;
}

void AMemoryTest::Return(AMyActor* Actor)
{
    if (Actor)
    {
        Actor->SetActorHiddenInGame(true);
        Actor->SetActorEnableCollision(false);
    }
}
