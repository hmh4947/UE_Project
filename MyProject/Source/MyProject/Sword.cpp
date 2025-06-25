// Fill out your copyright notice in the Description page of Project Settings.


#include "Sword.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "WarriorCharacter.h"

// Sets default values
ASword::ASword()
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));
	
	RootComponent = Weapon;
	Weapon->SetRelativeScale3D(FVector(90.0f, 90.0f, 90.0f));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Weapon(TEXT("'/Game/Blade_BlackKnight/SK_Blade_BlackKnight.SK_Blade_BlackKnight'"));


	if (SK_Weapon.Succeeded()) {
		Weapon->SetSkeletalMesh(SK_Weapon.Object);
		
	}
	else {
		UE_LOG(LogTemp, Warning, (TEXT("NOT SPAWN")));
	}
	Weapon->SetCollisionProfileName(TEXT("NoCollision"));

	
}

void ASword::MeleeTrace()
{
	
}

// Called when the game starts or when spawned
void ASword::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

