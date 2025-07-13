#include "AIActorComponent.h"
#include "AI_NPC/AIController/AINPCController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"
#include "AIController.h"
#include "Engine/World.h"
#include "AI_NPC/AIController/GhostAIController.h"

UAIActorComponent::UAIActorComponent()
{
    PrimaryComponentTick.bCanEverTick = false;  
}

void UAIActorComponent::BeginPlay()
{
    Super::BeginPlay();

    if (GEngine)
    {
        GEngine->Exec(GetWorld(), TEXT("ShowNavigation"));
    }

    GetWorld()->GetTimerManager().SetTimer(DistanceCheckTimerHandle, this, &UAIActorComponent::CheckPlayerDistance, 1.0f, true);

}

void UAIActorComponent::CheckPlayerDistance()
{
    if (!bHasInteractedWithPlayer) return;  // 대화를 하지 않았다면 아무것도 하지 않음

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!PlayerPawn || !GetOwner()) return;

    AActor* Owner = GetOwner();
    float Distance = FVector::Dist(PlayerPawn->GetActorLocation(), Owner->GetActorLocation());

    const float TeleportMinThreshold = 2000.f;
    const float TeleportMaxThreshold = 3000.f;
    const float FollowThreshold = 10.f;

    if (Distance > TeleportMinThreshold && Distance < TeleportMaxThreshold)
    {
        FVector TeleportLocation = PlayerPawn->GetActorLocation() + PlayerPawn->GetActorForwardVector() * -100.f;
        Owner->SetActorLocation(TeleportLocation);
        UE_LOG(LogTemp, Warning, TEXT("AINPC teleported behind player."));
        return;
    }

    APawn* OwnerPawn = Cast<APawn>(Owner);
    if (OwnerPawn)
    {
        if (AAINPCController* AIController = Cast<AAINPCController>(OwnerPawn->GetController()))
        {
            if (Distance > FollowThreshold)
            {
                AIController->GetBlackboardComponent()->SetValueAsObject("Target", PlayerPawn);
            }
            else
            {
                AIController->GetBlackboardComponent()->ClearValue("Target");
            }
        }
    }
}


