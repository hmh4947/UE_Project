// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Actor/VideoWidgetActor.h"
#include "VideoWidgetActor.h"

AVideoWidgetActor::AVideoWidgetActor()
{
}

void AVideoWidgetActor::BeginPlay()
{
	playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (!playerCharacter) return;
	



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

void AVideoWidgetActor::ClosedWidget()
{
	this->LevelStreamingWidget->SetVisibility(ESlateVisibility::Collapsed);
	this->Destroy();
}
