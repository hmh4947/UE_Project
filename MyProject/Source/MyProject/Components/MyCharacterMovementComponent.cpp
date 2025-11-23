// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProject/Components/MyCharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h" 
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"


#include "DrawDebugHelpers.h"



void UMyCharacterMovementComponent::PerformMovement(float DeltaTime)
{
    bool bCheck = false;
    if (!CharacterOwner || !CharacterOwner->GetMesh())
    {
        Super::PerformMovement(DeltaTime);
        return;
    }

    UAnimInstance* AnimInstance = CharacterOwner->GetMesh()->GetAnimInstance();
    if (!AnimInstance)
    {
        Super::PerformMovement(DeltaTime);
        return;
    }
    UAnimMontage* CurrentMontage = AnimInstance->GetCurrentActiveMontage();


    if (CurrentMontage)
    {
        const FName MontageName = CurrentMontage->GetFName();

        if (MontageName == FName("AM_SwordSlash"))
        {
            bCheck = true;
        }
    }

    FRootMotionMovementParams RMParams = CharacterOwner->GetMesh()->ConsumeRootMotion();
    FVector RootMotionDelta = FVector::ZeroVector;
    if (RMParams.bHasRootMotion)
    {
        FTransform RootMotionTransform = RMParams.GetRootMotionTransform();

        FTransform WorldTM = CharacterOwner->GetMesh()->ConvertLocalRootMotionToWorld(RootMotionTransform);
        RootMotionDelta = WorldTM.GetTranslation(); // 이동량만 추출

    }
    FVector Start = UpdatedComponent->GetComponentLocation();
    FVector End = Start + RootMotionDelta;
    FHitResult HitResult;
    FRotator Rotator = UpdatedComponent->GetComponentQuat().Rotator();
    if (bCheck)
    {
        if (IsFloorBelow(End))
        {
            // 바닥이 있으면 그대로 이동
         
            AnimInstance->RootMotionMode = ERootMotionMode::RootMotionFromEverything;
            SafeMoveUpdatedComponent(RootMotionDelta, Rotator, true, HitResult);
        }

        else
        {
            // 바닥 없으면 최대 안전 거리 계산 (binary search)
            float Low = 0.f, High = 1.f;
            for (int i = 0; i < 6; ++i) // 반복 횟수로 정확도 조절
            {
                float Mid = (Low + High) * 0.5f;
                FVector TestPos = Start + RootMotionDelta * Mid;
                if (IsFloorBelow(TestPos))
                    Low = Mid;
                else
                    High = Mid;
            }

            FVector SafeDelta = RootMotionDelta * Low;
            if (!SafeDelta.IsNearlyZero())
            {
                
                SafeMoveUpdatedComponent(SafeDelta, Rotator, true, HitResult);
            }

            // Root Motion은 소모되므로 남은 이동량은 버려집니다.
            // 애니메이션은 끝까지 재생됩니다.
            AnimInstance->RootMotionMode = ERootMotionMode::IgnoreRootMotion;
        }
    }
    else
    {
        // 다른 일반 애니메이션은 검사 없이 Root Motion 그대로 적용
        if (!RootMotionDelta.IsNearlyZero())
        {
            SafeMoveUpdatedComponent(RootMotionDelta, Rotator, true, HitResult);
        }
    }
    // 기본 이동 처리
    Super::PerformMovement(DeltaTime);
}

bool UMyCharacterMovementComponent::IsFloorBelow(const FVector& Point) const
{

    if (!CharacterOwner) return false;

    FVector Forward = CharacterOwner->GetActorForwardVector();

    FVector TraceStart = UpdatedComponent->GetComponentLocation() + FVector(0.f, 0.f, 50.f); // 약간 위에서
    FVector TraceEnd = TraceStart + Forward * 200.f; // 200 유닛 앞
    TraceEnd.Z -= 300.f;
    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(GetOwner());

    bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, Params);
#if WITH_EDITOR
    // 디버그용 선 그리기
    //DrawDebugLine(GetWorld(), TraceStart, TraceEnd, bHit ? FColor::Green : FColor::Red, false, 1.f, 0, 2.f);
#endif
    return bHit && Hit.bBlockingHit;
}