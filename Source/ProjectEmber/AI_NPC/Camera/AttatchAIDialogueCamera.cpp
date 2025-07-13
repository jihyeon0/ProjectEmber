#include "AttatchAIDialogueCamera.h"

UAttatchAIDialogueCamera::UAttatchAIDialogueCamera()
{
    // �⺻ ī�޶� ���� (�ʿ� �� ���� ����)
    SetRelativeLocation(FVector(300.f, 80.f, 180.f));     // �� + ������ + ��
    SetRelativeRotation(FRotator(-10.f, -160.f, 0.f));    // �ణ �����ٺ��� �÷��̾� ����
    SetFieldOfView(60.f);                                            // ���� �þ߰����� ���ߵ� ���
}

void UAttatchAIDialogueCamera::BeginPlay()
{
    Super::BeginPlay();

    // �ʱ�ȭ �α�
    UE_LOG(LogTemp, Warning, TEXT("UAttatchAIDialogueCamera::BeginPlay() - Initialized"));
}