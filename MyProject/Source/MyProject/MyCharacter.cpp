// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "EnhancedInputComponent.h"
#include "MyProjectHUD.h"



// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Begin함수 동작한 직후 Tick 함수가 계속 동작하도록 만듦
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	//카메라 회전시 캐릭터가 회전하지 않도록 고정
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//캐릭터 이동방향으로 카메라 회전
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f);

	//캐릭터가 특정 평면에서만 이동하도록 제한
	GetCharacterMovement()->bConstrainToPlane = true;

	//평면을 벗어난 상태시 초기위치를 지정된 평면에 자동으로 정렬
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	//스프링 암이 절대 회전 값을 사용
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	SpringArmComponent->TargetArmLength = 800.0f;
	SpringArmComponent->SetRelativeRotation(FRotator(-60.0f, 45.0f, 0.0f));

	//카메라가 벽을 뚫지 못함,벽에 닿을 시 캐릭터와의 간격을 좁힘
	SpringArmComponent->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	//캐릭터 회전시 카메라가 회전하지 않도록 고정
	CameraComponent->bUsePawnControlRotation = false;


}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);



}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	HUD = Cast<AMyProjectHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	
	
	
}

void AMyCharacter::Initialize()
{
}

// Called every frame
void AMyCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	
}


