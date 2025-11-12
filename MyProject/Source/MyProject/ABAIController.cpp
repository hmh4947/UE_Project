// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "HUDWidget.h"
#include "ClickMovePlayerController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "MyProject/Ai/MyTaskNode.h"

#include "SevargoEnemy.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Networking.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Common/TcpSocketBuilder.h"
#include "Serialization/JsonSerializer.h"
#include "Dom/JsonObject.h"
#include "Skill/SkillComponent.h"
#include "Skill/Skills.h"
#include "Skill/TrainSkills.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/FileHelper.h"


const FName AABAIController::HomePosKey(TEXT("HomePos"));
const FName AABAIController::PatrolPosKey(TEXT("PatrolPos"));
const FName AABAIController::TargetKey(TEXT("Target"));
const FName AABAIController::MontageIndexKey(TEXT("MontageIndex"));
AABAIController::AABAIController()
{

	//비헤이비어 트리 오브젝트 가져오기
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Game/Enemy/BT_EnemyAI.BT_EnemyAI"));
	if (BT.Succeeded()) {
		BehaviorTree = BT.Object;
	}

	//블랙보드 오브젝트 가져오기
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BB(TEXT("/Game/Enemy/BB_EnemyAI.BB_EnemyAI"));
	if (BB.Succeeded()) {
		BlackboardData = BB.Object;
	}
	
}




void AABAIController::UpdateEnemyHealthPercent(float HealthPercent)
{
	//컨트롤러 가져오기
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();

	AClickMovePlayerController* controller = Cast<AClickMovePlayerController>(Controller);
	
	//컨트롤러의 HUDWidget 변수 사용
	if (controller->HUDWidget != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("healthComponent"));
		controller->HUDWidget->UpdateEnemyHealthPercent(HealthPercent);

	}
	
}

//빙의 실행
void AABAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BlackboardData, Blackboard))
	{
		Blackboard->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		RunBehaviorTree(BehaviorTree);
	}
	
}

//빙의 해제
void AABAIController::OnUnPossess()
{
	Super::OnUnPossess();
	
}
	




void AABAIController::Tick(float DeltaTime)
{

}

void AABAIController::RegisterTaskNode(UMyTaskNode* node)
{
	ManagedTasks.Add(node);
}



void AABAIController::BeginPlay()
{
	Super::BeginPlay();
	

}

FString AABAIController::SendStateToExternal()
{
	TArray<TSharedPtr<FJsonValue>> SkillArray;
	FString ServerIP = TEXT("127.0.0.1");
	int32 ServerPort = 9999;
	
	APawn* pawn = GetPawn();
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

int32 AABAIController::SendServer(const FString& JsonStr)
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

void AABAIController::TestSendRLDecision()
{
	APawn* pawn = GetPawn();
	if (!pawn) return;
	ASevargoEnemy* Enemy = Cast<ASevargoEnemy>(pawn);
	if (!Enemy) return;

	FString JsonString = SendStateToExternal();
	int32 ActionIndex = SendServer(JsonString);

	APawn* ControlledPawn = GetPawn();
	ACharacter* ControlledCharacter = Cast<ACharacter>(GetPawn());

	UE_LOG(LogTemp, Log, TEXT("RL Server to actionindex: %d"), ActionIndex);

	if (ActionIndex < 0) return;

	const TArray<ASkills*> Skills = Enemy->SkillComponent->GetActivatableSkills();
	if (ControlledCharacter && Skills[ActionIndex])
	{
		Skills[ActionIndex]->SkillExecute(ControlledCharacter);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("not valid: %d"), ActionIndex);
	}
}