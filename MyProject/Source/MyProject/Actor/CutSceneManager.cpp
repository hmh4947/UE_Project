// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Actor/CutSceneManager.h"
#include "CutSceneManager.h"

#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "MediaSoundComponent.h"
#include "MediaPlayer.h"
#include "MyProject/WarriorCharacter.h"
#include "MyProject/HUDWidget.h"
#include "Components/ProgressBar.h"
#include "MyProject/ClickMovePlayerController.h"
#include "MyProject/SevargoEnemy.h"
#include "MyProject/UI/DialogWidget.h"
#include "MyProject/UI/DialogNodeAsset.h"

// Sets default values
ACutSceneManager::ACutSceneManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ACutSceneManager::OnStartcutsceneEndReached()
{
	ClosedWidget();
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f); // 원래 속도로
	FVector location = FVector(-3240.f, -20.f, 140.f);
	FRotator rotation = FRotator::ZeroRotator; // 기본값


	ASevargoEnemy* SpawnedActor = GetWorld()->SpawnActor<ASevargoEnemy>(spawnEnemy, location, rotation);
	if (!SpawnedActor) return;
	SetVisibleEnemyHealthBar();

}

void ACutSceneManager::OnEventcutsceneEndReached()
{
	ClosedWidget();
	if (!eventDialogAsset)return;

	//Dialog->RootNode= eventDialogAsset;
	//위젯 이벤트


}

void ACutSceneManager::OnEndcutsceneEndReached()
{
	ClosedWidget();
	
}

void ACutSceneManager::ClosedWidget()
{
	MediaPlayer->OnEndReached.Clear();
	mediaPlayerWidget->SetVisibility(ESlateVisibility::Collapsed);

	
}

void ACutSceneManager::SetVisibleEnemyHealthBar()
{
	AWarriorCharacter* warrior = Cast<AWarriorCharacter>(playerCharacter);

	if (!warrior) return;
	AClickMovePlayerController* controller = Cast< AClickMovePlayerController>(warrior->GetController());
	controller->HUDWidget->EnemyHealthBar->SetVisibility(ESlateVisibility::Visible);




}



void ACutSceneManager::PlayCutScene(ECutSceneType type)
{

	if (!CutsceneMap.Contains(type))return;

	playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (!playerCharacter)return;
	
	UGameplayStatics::UnloadStreamLevel(
		this,
		level,
		FLatentActionInfo(),
		false //비동기
	);




	UMediaSource* mediaSource = CutsceneMap[type];
	if (MediaPlayer && mediaSource)
	{
		mediaPlayerWidget->SetVisibility(ESlateVisibility::Visible);
		MediaPlayer->OpenSource(mediaSource);
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.f); // 게임 속도 0 → 움직임 멈춤

		//타입에 따른 영상이 끝나는 시점 이벤트
		if (type == ECutSceneType::BossStart)
		{
			MediaPlayer->OnEndReached.AddDynamic(this, &ACutSceneManager::OnStartcutsceneEndReached);
		}
		if (type == ECutSceneType::BossEvent)
		{
			MediaPlayer->OnEndReached.AddDynamic(this, &ACutSceneManager::OnEventcutsceneEndReached);
		}
		if (type == ECutSceneType::BossEnd)
		{
			MediaPlayer->OnEndReached.AddDynamic(this, &ACutSceneManager::OnEndcutsceneEndReached);
		}
	

		
	}
	
}

void ACutSceneManager::SetMediaPlayerWidget(UUserWidget* widget)
{
	mediaPlayerWidget = widget;
}

// Called when the game starts or when spawned
void ACutSceneManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACutSceneManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

