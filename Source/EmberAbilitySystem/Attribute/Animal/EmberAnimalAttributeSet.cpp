﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "EmberAnimalAttributeSet.h"

UEmberAnimalAttributeSet::UEmberAnimalAttributeSet()
{
}

void UEmberAnimalAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
}

void UEmberAnimalAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
}

bool UEmberAnimalAttributeSet::PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data)
{
	return Super::PreGameplayEffectExecute(Data);
}

void UEmberAnimalAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

void UEmberAnimalAttributeSet::InitFromData(const FEmberAnimalAttributeData& Data)
{
	InitFullness(Data.Fullness);
	InitWalkSpeed(Data.WalkSpeed);
	InitWildPower(Data.WildPower);
}