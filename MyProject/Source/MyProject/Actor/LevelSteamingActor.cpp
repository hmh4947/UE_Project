// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Actor/LevelSteamingActor.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

#include "MediaSoundComponent.h"
#include "MediaPlayer.h"
#include "MyProject/WarriorCharacter.h"
#include "MyProject/HUDWidget.h"
#include "Components/ProgressBar.h"
#include "MyProject/ClickMovePlayerController.h"
// Sets default values
ALevelSteamingActor::ALevelSteamingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	BoxCollision->SetupAttachment(RootComponent);
	MediaSound = CreateDefaultSubobject<UMediaSoundComponent>(TEXT("MediaSound"));
	MediaSound->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALevelSteamingActor::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ALevelSteamingActor::BeginOverlap);
	
}

// Called every frame
void ALevelSteamingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelSteamingActor::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	
	if (OtherActor == playerCharacter)
	{
		UGameplayStatics::UnloadStreamLevel(
			this,
			level,
			FLatentActionInfo(),
			false //비동기
		);
		
		
	
		LevelStreamingWidget = CreateWidget<UUserWidget>(GetWorld(), spawnWidget);
		if (LevelStreamingWidget)
		{
			LevelStreamingWidget->AddToViewport();
			if (MediaSound && MediaPlayer)
			{
				MediaSound->SetMediaPlayer(MediaPlayer);
				MediaPlayer->OpenSource(MyMediaSource);
				//영상이 끝나는 시점 이벤트
				MediaPlayer->OnEndReached.AddDynamic(this, &ALevelSteamingActor::ClosedWidget);
			
			
			}
		}
	}


}

void ALevelSteamingActor::ClosedWidget()
{
	
	LevelStreamingWidget->SetVisibility(ESlateVisibility::Collapsed);
	FVector location = FVector(-3240.f, -20.f, 140.f);
	FRotator rotation = FRotator::ZeroRotator; // 기본값

	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(spawnEnemy, location, rotation);
	SetVisibleEnemyHealthBar();
	this->Destroy();
	

	
}

void ALevelSteamingActor::SetVisibleEnemyHealthBar()
{	
	AWarriorCharacter* warrior = Cast<AWarriorCharacter>(playerCharacter);
	
	if (!warrior) return;
	AClickMovePlayerController* controller=Cast< AClickMovePlayerController>(warrior->GetController());
	controller->HUDWidget->EnemyHealthBar->SetVisibility(ESlateVisibility::Visible);
	

}

