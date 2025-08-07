// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Ai/BTTask_RLState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RLState.h"
#include "MyProject/ABAIController.h"
#include "AIController.h"
#include "GameFramework/Pawn.h"

#include "MyProject/SevargoEnemy.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Networking.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Common/TcpSocketBuilder.h"
#include "Serialization/JsonSerializer.h"
#include "Dom/JsonObject.h"
#include "MyProject/Skill/SkillComponent.h"
#include "MyProject/Skill/Skills.h"
#include "MyProject/Skill/TrainSkills.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/FileHelper.h"
UBTTask_RLState::UBTTask_RLState()
{
	NodeName = TEXT("RLState");
	TotalRewardArray.Empty();
}

EBTNodeResult::Type UBTTask_RLState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
	if (!BB) return EBTNodeResult::Failed;
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;
	AABAIController* EnemyContorller = Cast<AABAIController>(AIController);
	if(!EnemyContorller)return EBTNodeResult::Failed;
	APawn* pawn = EnemyContorller->GetPawn();
	if(!pawn) return EBTNodeResult::Failed;
	TestSendRLDecision(pawn, BB);
	return EBTNodeResult::Type();
}

void UBTTask_RLState::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
}

FString UBTTask_RLState::SendStateToExternal(APawn* pawn)
{
	TArray<TSharedPtr<FJsonValue>> SkillArray;

	FString ServerIP = TEXT("127.0.0.1");
	int32 ServerPort = 9999;
	
	
	int32 SkillIndex = 0;

	if (pawn)
	{
		ASevargoEnemy* Enemy = Cast<ASevargoEnemy>(pawn);
		if (Enemy) {
			for (ASkills* Skill : Enemy->SkillComponent->GetActivatableSkills())
			{
				if (!Skill) continue;

				if (ATrainSkills* TrainSkill = Cast<ATrainSkills>(Skill))
				{
					float Reward = 0.0f;
					if(TotalRewardArray.IsValidIndex(SkillIndex))
					{
						Reward = TotalRewardArray[SkillIndex];
					}
					TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
					JsonObject->SetNumberField(TEXT("total_reward"), Reward);
					JsonObject->SetNumberField(TEXT("skill_type"), static_cast<int32>(TrainSkill->GetSkillType()));
					JsonObject->SetNumberField(TEXT("hit_count"), TrainSkill->getHitCount());
					JsonObject->SetNumberField(TEXT("is_hit"), TrainSkill->GetIsHit());
					JsonObject->SetNumberField(TEXT("skill_active"), TrainSkill->GetActiveSkill() ? 1 : 0);

					SkillArray.Add(MakeShareable(new FJsonValueObject(JsonObject)));
					SkillIndex++;
				}

			}
		}
	}

	TSharedPtr<FJsonObject> RootObj = MakeShareable(new FJsonObject);
	RootObj->SetArrayField(TEXT("skills"), SkillArray);

	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(RootObj.ToSharedRef(), Writer);

	UE_LOG(LogTemp, Warning, TEXT("Send JSON: %s"), *OutputString);

	return OutputString;
	
}

int32 UBTTask_RLState::SendServer(const FString& JsonStr)
{
	bool bIsValid = false;
	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	TSharedRef<FInternetAddr> Addr = SocketSubsystem->CreateInternetAddr();
	Addr->SetIp(TEXT("127.0.0.1"), bIsValid);
	Addr->SetPort(9999);

	if (!bIsValid)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid IP address"));
		return -1;
	}

	FSocket* Socket = SocketSubsystem->CreateSocket(NAME_Stream, TEXT("RLClientSocket"), false);
	if (!Socket)
	{
		UE_LOG(LogTemp, Error, TEXT("Socket creation failed"));
		return -1;
	}

	if (!Socket->Connect(*Addr))
	{
		UE_LOG(LogTemp, Error, TEXT("Not Connected to Python Server"));
		return -1;
	}
	//UTF-8 인코딩
	FTCHARToUTF8 Convert(*JsonStr);
	int32 BytesSent = 0;
	Socket->Send((uint8*)Convert.Get(), Convert.Length(), BytesSent);

	// 서버 응답 받기 (예: "1", "0" 등)
	TArray<uint8> Response;
	Response.SetNumUninitialized(2048);
	int32 BytesRead = 0;
	Socket->Recv(Response.GetData(), Response.Num(), BytesRead);

	Socket->Close();
	ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket);
	// 문자열을 정수로 변환
	FString ResponseStr = FString(ANSI_TO_TCHAR(reinterpret_cast<const char*>(Response.GetData())));
	ResponseStr = ResponseStr.Left(BytesRead);
	TSharedPtr<FJsonObject> JsonParsed;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseStr);

	if (!FJsonSerializer::Deserialize(Reader, JsonParsed) || !JsonParsed.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to parse JSON response"));
		UE_LOG(LogTemp, Warning, TEXT("Raw Response: %s"), *ResponseStr);
		UE_LOG(LogTemp, Warning, TEXT("BytesRead: %d"), BytesRead);

		return -1;
	}

	int32 ActionIndex = JsonParsed->GetIntegerField(TEXT("action"));
	const TArray<TSharedPtr<FJsonValue>> RewardArray = JsonParsed->GetArrayField(TEXT("reward"));

	for (int32 i = 0; i < RewardArray.Num(); ++i)
	{
		float Reward = static_cast<float>(RewardArray[i]->AsNumber());

		if (TotalRewardArray.IsValidIndex(i))
		{
			//누적
			TotalRewardArray[i] += Reward;
		}
		else
		{
			TotalRewardArray.Add(Reward);
		}

		UE_LOG(LogTemp, Warning, TEXT("Reward[%d]: %f"), i, TotalRewardArray[i]);
	}
	return ActionIndex;

}

void UBTTask_RLState::TestSendRLDecision(APawn* pawn, UBlackboardComponent* BB)
{
	if (!pawn) return;
	ASevargoEnemy* Enemy = Cast<ASevargoEnemy>(pawn);
	if (!Enemy) return;
	
	FString JsonString = SendStateToExternal(pawn);
	int32 ActionIndex = SendServer(JsonString);


	UE_LOG(LogTemp, Log, TEXT("RL Server to actionindex: %d"), ActionIndex);


	SetReceivedSkillIndex(ActionIndex,BB,pawn);
}

int32 UBTTask_RLState::GetReceivedSkillIndex() const
{
	return receivedIndex;
}

void UBTTask_RLState::UpdateReward(float reward)
{
	TotalReward += reward;
}

void UBTTask_RLState::SetReceivedSkillIndex(int32 index, UBlackboardComponent* BB, APawn* pawn)
{
	

	if (!BB) return;
	BB->SetValueAsInt("MontageIndex", index);
	
	UE_LOG(LogTemp, Warning, TEXT("skill_Index: %d"), index);
	if(pawn)
	{
		ASevargoEnemy* Enemy = Cast<ASevargoEnemy>(pawn);
		if (Enemy) {
			ASkills* skill = Enemy->SkillComponent->GetActivatableSkill(index);
			Enemy->SkillComponent->setCurrentSkill(skill);
		}
	}

	
}


