// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LeakyDialogActor.generated.h"
USTRUCT(BlueprintType)
struct FDialogLine
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
	UTexture2D* SpeakerImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialog")
	FText DialogText;
};
UCLASS()
class MYPROJECT_API ALeakyDialogActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALeakyDialogActor();
	UFUNCTION()
	void SpawnDialogs();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 대화 배열을 액터에서 직접 관리
	UPROPERTY(EditAnywhere, Category = "Dialog")
	TArray<FDialogLine> Dialogs;

	UPROPERTY(EditAnywhere, Category = "Dialog")
	TSubclassOf<class ULeakyDialogWidget> DialogWidgetClass;

	int32 CurrentIndex;


private:
	// 릭 유발 (GC 추적 안 됨)
	ULeakyDialogWidget* CurrentWidget;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
