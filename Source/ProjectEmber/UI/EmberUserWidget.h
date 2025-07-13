﻿#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySystemInterface.h"
#include "EMSActorSaveInterface.h"
#include "EmberUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTEMBER_API UEmberUserWidget : public UUserWidget, public IAbilitySystemInterface, public IEMSActorSaveInterface
{
	GENERATED_BODY()

public:
	virtual void SetAbilitySystemComponent(class AActor* InOwner);
	UFUNCTION(BlueprintCallable, Category = "AbilitySystem")
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	UPROPERTY(EditAnywhere, Category = "AbilitySystem")
	TObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent;
};
