#include "PlayerQuestWidget.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Quest/Data/QuestDataAsset.h"
#include "Quest/QuestSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UPlayerQuestWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Border_512)
	{
		Border_512->SetVisibility(ESlateVisibility::Collapsed); // �⺻�� ����
	}
}


void UPlayerQuestWidget::SetQuestInfoFromDataAsset(const UQuestDataAsset* QuestAsset, bool bIsComplete, bool bIsAccepted, bool bShowStepComplete, int32 StepIndex)
{
	if (!QuestAsset) return;

	// �Ϸ� ���� ó��
	if (Border_512)
	{
		Border_512->SetVisibility((bIsComplete || bShowStepComplete) ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
	}

	// ���� ��: ��ü ���� ǥ��
	if (!bIsAccepted)
	{
		if (QuestNameText) QuestNameText->SetText(QuestAsset->QuestName);
		if (QuestDescriptionText) QuestDescriptionText->SetText(QuestAsset->QuestDescription);
		if (LocationText) LocationText->SetText(QuestAsset->TargetLocationTag);

		if (RewardText)
		{
			int32 TotalGold = 0, TotalExp = 0;
			for (const FQuestStep& Step : QuestAsset->Steps)
			{
				for (const FQuestRewardData& Reward : Step.Rewards)
				{
					if (Reward.RewardTag == FGameplayTag::RequestGameplayTag("Reward.Gold"))
						TotalGold += Reward.RewardCount;
					else if (Reward.RewardTag == FGameplayTag::RequestGameplayTag("Reward.Exp"))
						TotalExp += Reward.RewardCount;
				}
			}
			FString RewardStr = FString::Printf(TEXT("%d Gold / %d EXP"), TotalGold, TotalExp);
			RewardText->SetText(FText::FromString(RewardStr));
		}

		if (ObjectiveNameText)
		{
			FString Objectives;
			for (const FQuestStep& Step : QuestAsset->Steps)
			{
				FString Line = Step.StepObjectiveName.IsEmpty()
					? Step.StepID.ToString()
					: Step.StepObjectiveName.ToString();
				Objectives += Line + TEXT("\n");
			}
			ObjectiveNameText->SetText(FText::FromString(Objectives));
		}
		return;
	}

	// ���� ��: Ư�� StepIndex ǥ��
	if (!QuestAsset->Steps.IsValidIndex(StepIndex)) return;

	const FQuestStep& Step = QuestAsset->Steps[StepIndex];

	if (QuestNameText) QuestNameText->SetText(Step.StepName.IsEmpty() ? QuestAsset->QuestName : Step.StepName);
	if (QuestDescriptionText) QuestDescriptionText->SetText(Step.StepQuestDescription.IsEmpty() ? QuestAsset->QuestDescription : Step.StepQuestDescription);
	if (LocationText) LocationText->SetText(Step.StepTargetLocationTag.IsEmpty() ? QuestAsset->TargetLocationTag : Step.StepTargetLocationTag);

	if (RewardText)
	{
		int32 Gold = 0, Exp = 0;
		for (const FQuestRewardData& Reward : Step.Rewards)
		{
			if (Reward.RewardTag == FGameplayTag::RequestGameplayTag("Reward.Gold"))
				Gold += Reward.RewardCount;
			else if (Reward.RewardTag == FGameplayTag::RequestGameplayTag("Reward.Exp"))
				Exp += Reward.RewardCount;
		}
		FString RewardStr = FString::Printf(TEXT("%d Gold / %d EXP"), Gold, Exp);
		RewardText->SetText(FText::FromString(RewardStr));
	}

	if (ObjectiveNameText)
	{
		FString CombinedObjectives;

		// ���� ��� ���� ����
		for (const UQuestCondition* Condition : Step.Conditions)
		{
			if (Condition)
			{
				FString ConditionText;
				const bool bIsFulfilled = Condition->IsFulfilled();

				// �̸� ó��
				FString NameStr = Condition->ConditionName.IsEmpty()
					? TEXT("")  // �⺻ �̸�
					: Condition->ConditionName.ToString();

				ConditionText = FString::Printf(TEXT("- %s: %d / %d%s"),
					*NameStr,
					Condition->CurrentCount,
					Condition->RequiredCount,
					bIsFulfilled ? TEXT(" (Complete)") : TEXT(""));

				CombinedObjectives += ConditionText + TEXT("\n");
			}
		}

		// ����Ʈ ��ǥ ����� ������ ��� ����
		if (!Step.StepObjectiveName.IsEmpty())
		{
			const FString Header = Step.StepObjectiveName.ToString() + TEXT("\n");
			CombinedObjectives = Header + CombinedObjectives;
		}

		ObjectiveNameText->SetText(FText::FromString(CombinedObjectives.TrimEnd()));
	}
}