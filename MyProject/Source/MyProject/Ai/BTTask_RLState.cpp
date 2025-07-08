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
}

EBTNodeResult::Type UBTTask_RLState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) return EBTNodeResult::Failed;
	AABAIController* EnemyContorller = Cast<AABAIController>(AIController);
	if(!EnemyContorller)return EBTNodeResult::Failed;
	APawn* pawn = EnemyContorller->GetPawn();
	if(!pawn) return EBTNodeResult::Failed;
	TestSendRLDecision(pawn);
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
	
	if (pawn)
	{
		ASevargoEnemy* Enemy = Cast<ASevargoEnemy>(pawn);
		if (Enemy) {
			for (ASkills* Skill : Enemy->SkillComponent->GetActivatableSkills())
			{
				if (!Skill) continue;

				if (ATrainSkills* TrainSkill = Cast<ATrainSkills>(Skill))
				{

					TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
					JsonObject->SetNumberField(TEXT("skill_type"), static_cast<int32>(TrainSkill->GetSkillType()));
					JsonObject->SetNumberField(TEXT("hit_count"), TrainSkill->getHitCount());
					JsonObject->SetNumberField(TEXT("is_hit"), TrainSkill->GetIsHit());
					JsonObject->SetNumberField(TEXT("skill_active"), TrainSkill->GetActiveSkill() ? 1 : 0);

					SkillArray.Add(MakeShareable(new FJsonValueObject(JsonObject)));
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
	uint8 Response[128] = {};
	int32 BytesRead = 0;
	Socket->Recv(Response, sizeof(Response), BytesRead);

	Socket->Close();
	ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket);
	FString ResponseStr = FString(ANSI_TO_TCHAR(reinterpret_cast<const char*>(Response)));

	return FCString::Atoi(*ResponseStr);
	
}

void UBTTask_RLState::TestSendRLDecision(APawn* pawn)
{
	if (!pawn) return;
	ASevargoEnemy* Enemy = Cast<ASevargoEnemy>(pawn);
	if (!Enemy) return;
	
	FString JsonString = SendStateToExternal(pawn);
	int32 ActionIndex = SendServer(JsonString);

	//APawn* ControlledPawn = GetPawn();
	//ACharacter* ControlledCharacter = Cast<ACharacter>(GetPawn());

	UE_LOG(LogTemp, Log, TEXT("RL Server to actionindex: %d"), ActionIndex);

	if (ActionIndex < 0) return;
	
	const TArray<ASkills*> Skills = Enemy->SkillComponent->GetActivatableSkills();
	if (Enemy && Skills[ActionIndex])
	{
		Skills[ActionIndex]->SkillExecute(Enemy);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("not valid: %d"), ActionIndex);
	}
}
