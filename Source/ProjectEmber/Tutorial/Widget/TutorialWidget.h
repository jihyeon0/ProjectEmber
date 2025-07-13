// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Tutorial/DataAssest/TutorialDataAsset.h"
#include "TutorialWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTEMBER_API UTutorialWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual void NativeConstruct() override;

    UFUNCTION(BlueprintCallable)
    void SetImageTexture(UTexture2D* NewImage);

	UFUNCTION(BlueprintCallable)
    void SetMediaImageTexture(UTexture* NewImage);
	
    UFUNCTION(BlueprintCallable)
    void ShowTutorial(bool bShow);

    UFUNCTION(BlueprintCallable)
	void SetTutorialData(const FTutorialData& Data, int32 CurrentIndex, int32 TotalCount);

    UFUNCTION()
    void OnCloseButtonClicked();

	UFUNCTION()
	void OnNextButtonClicked();

	UPROPERTY(meta = (BindWidget))
    class UImage* KeylImage;

	UPROPERTY(meta = (BindWidget))
	class UImage* MediaImage;
	
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* TutorialNameText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* TutorialDescriptionText;

    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* BoderAnimation;

    UPROPERTY(meta = (BindWidget))
    class UButton* TutorialButton;

	UPROPERTY(meta = (BindWidget))
	UButton* NextButton;
};