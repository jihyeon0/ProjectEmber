// Fill out your copyright notice in the Description page of Project Settings.


#include "AIAnimal/BT/BTTask_AttackTarget.h"

#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ProjectEmber/AIAnimal/BaseAIAnimal.h"

UBTTask_AttackTarget::UBTTask_AttackTarget()
{
	NodeName = TEXT("AttackTarget");
}

EBTNodeResult::Type UBTTask_AttackTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController =  OwnerComp.GetAIOwner();
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}

	APawn* AIPawn = AIController->GetPawn();
	if (!AIPawn)
	{
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* BlackboardComp =	AIController->GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}

	//공격어빌리티 함수 호출
	ABaseAIAnimal* AICharacter = Cast<ABaseAIAnimal>(AIPawn);
	if (!AICharacter)
	{
		return EBTNodeResult::Failed;
	}
	
	// 공격중 겹침 + 자기 동물 태그랑 상대 태그랑 같으면 -> 공격 취소
	ABaseAIAnimal* AIAnimal = Cast<ABaseAIAnimal>(AIPawn);
	if (AIAnimal)
	{
		AIAnimal->SetHitCount(0);
		UObject* TargetObject = BlackboardComp->GetValueAsObject("TargetActor");
		if (ABaseAIAnimal* TargetActor = Cast<ABaseAIAnimal>(TargetObject))//가져왔는데 동물이면
		{
			if (TargetActor->GetIsDead())
			{
				Cast<AAIController>(AIAnimal->GetController())->GetBlackboardComponent()->SetValueAsName("NStateTag", "Animal.State.Idle");
				Cast<AAIController>(AIAnimal->GetController())->GetBlackboardComponent()->SetValueAsObject("TargetActor", nullptr);
				return EBTNodeResult::Failed;
			}
			if (Cast<ABaseAIAnimal>(AIPawn)->GetIdentityTag() == TargetActor->GetIdentityTag())
			{
				return EBTNodeResult::Failed;
			}
		}

		//아직 어빌리티가 실행중이면 어택노드가 진행중이라고 처리 -> 노드 들어올때마다 몽타주 재생 방지
		if (AICharacter->GetAbilitySystemComponent()->IsActive())
		{
			return EBTNodeResult::Failed;
		}
		FGameplayEventData Payload;
		Payload.EventTag = FGameplayTag::RequestGameplayTag("Trigger.Animal.Attack");
		Payload.Instigator = AICharacter;
		Payload.OptionalObject = AICharacter->GetMontage(FGameplayTag::RequestGameplayTag("Animal.Montage.Attack"));
		float PlayTime = AICharacter->GetMontage(FGameplayTag::RequestGameplayTag("Animal.Montage.Attack"))->GetPlayLength();
		BlackboardComp->SetValueAsFloat("AnimPlayTime",PlayTime);
		AICharacter->GetAbilitySystemComponent()->HandleGameplayEvent(Payload.EventTag, &Payload);
		return Super::ExecuteTask(OwnerComp, NodeMemory);
	}
	return EBTNodeResult::Failed;
}

//어빌리티 사용 이유 -> 몽타주 재생중인지 완료인지 판단할 수 있음