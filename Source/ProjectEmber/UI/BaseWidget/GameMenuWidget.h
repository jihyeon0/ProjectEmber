﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetSwitcher.h"
#include "GameMenuWidget.generated.h"

class UWidgetSwitcher;
class UBorder;

UCLASS()
class PROJECTEMBER_API UGameMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="UI|Layer")
	void Input_ToggleInventory();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="UI|Layer")
	void Input_ToggleQuest();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="UI|Layer")
	void Input_ToggleSkill();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="UI|Layer")
	void Input_TogglePause();
    /** Quest 위젯 안의 QuestContents를 찾아 업데이트하는 함수 */
    UFUNCTION(BlueprintCallable)
    void UpdateQuestInfoViaWidgetTree();

	UFUNCTION(BlueprintCallable, Category="UI|Layer")
	UUserWidget* GetSkillTreeWidget() const;

	UUserWidget* GetQuestListWidget() const;
public:
    // Toggle 시 접근할 수 있도록 public으로 설정
    UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
    UWidgetSwitcher* BaseWidgetSwitcher;

    UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
    UBorder* EmptyBorder;

	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	UUserWidget* WBP_SkillTree;
	
protected:
	
    /** 중간 퀘스트 래퍼 위젯 (블루프린트: WBP_Quest) */
    UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
    UUserWidget* WBP_Quest;
	

};
