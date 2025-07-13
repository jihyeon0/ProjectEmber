#include "GhostActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TimerManager.h"

UGhostActorComponent::UGhostActorComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UGhostActorComponent::BeginPlay()
{
    Super::BeginPlay();

    // 0.01�� �������� �ε巴�� �̵�
    GetWorld()->GetTimerManager().SetTimer(GhostFollowTimerHandle, this, &UGhostActorComponent::GhostFollowPlayer, 0.01f, true);
}

void UGhostActorComponent::GhostFollowPlayer()
{
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!PlayerPawn || !GetOwner()) return;

    AActor* Owner = GetOwner();
    FVector PlayerLocation = PlayerPawn->GetActorLocation();
    FVector OwnerLocation = Owner->GetActorLocation();

    float Distance = FVector::Dist(PlayerLocation, OwnerLocation);

    // �ʹ� �ָ� �����̵� + ������ ���󰡱� ����
    if (Distance > TeleportThreshold)
    {
        FVector TeleportLocation = PlayerLocation + PlayerPawn->GetActorForwardVector() * -100.f;
        Owner->SetActorLocation(TeleportLocation);
        UE_LOG(LogTemp, Warning, TEXT("Ghost NPC teleported behind player."));
        bIsFollowing = true; // ������ ���� ���·� ����
        return;
    }

    //  �����ϸ� ���� ����
    if (bIsFollowing)
    {
        if (Distance > StopThreshold)
        {
            // �̵�
            FVector Direction = (PlayerLocation - OwnerLocation).GetSafeNormal();
            FVector NewLocation = OwnerLocation + Direction * Speed * GetWorld()->GetDeltaSeconds();
            Owner->SetActorLocation(NewLocation);
        }
        else
        {
            // ���� �� ���� ���� ��ȯ
            Owner->SetActorLocation(PlayerLocation); // �Ϻ� ����
            bIsFollowing = false;
        }
    }
    else
    {
        //  ���� ���¸� �� Tick ������ �� �ٿ�!
        Owner->SetActorLocation(PlayerLocation);

        // �÷��̾ �ٽ� �־����� ���� ���·� ����
        if (Distance > StopThreshold)
        {
            bIsFollowing = true;
        }
    }

    // �׻� �ٶ󺸱�
    FVector ToPlayer = PlayerLocation - OwnerLocation;
    FRotator LookAtRotation = ToPlayer.Rotation();
    Owner->SetActorRotation(LookAtRotation);
}