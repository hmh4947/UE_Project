// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MemoryTest.generated.h"

class AMyActor;
UCLASS()
class MYPROJECT_API AMemoryTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMemoryTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere)
	TArray<AMyActor*> ActorPool;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AMyActor> MyActorClass;

	//초기화
	void Initialize();
	void SpawnFromPool();
	void ReturnToPool(AMyActor* Actor);
	AMyActor* ReSpawn();
	void Return(AMyActor* Actor);

	int32 poolSize=20;
	float SpawnInterval = 0.1f;   // 0.1초 간격
	float SpawnDuration = 40.0f;
	float ElapsedTime = 0.0f;
private:
	FTimerHandle QuitTimerHandle;

	// 액터를 생성 타이머
	FTimerHandle SpawnTimerHandle;

	FTimerHandle SpawnLoopTimerHandle;

	void QuitGame();



	// Raw pointer 배열 (의도적으로 누수 발생)
	
	TArray<AMyActor*> RawActorArray;

	void SpawnActors();

	void StartSpawnLoop();

	void StopSpawnLoop();


};
