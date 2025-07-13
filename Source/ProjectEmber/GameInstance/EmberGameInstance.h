#pragma once

#include "CoreMinimal.h"
#include "EnumSet.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "Character/InputHandler/EmberKeyMappingEntry.h"
#include "InputMappingContext.h"
#include "UObject/SoftObjectPtr.h"
#include "InputTriggers.h"
#include "InputModifiers.h"
#include "EasyMultiSave.h"
#include "GameInstance/EmberVideoSettings.h"
#include "GameInstance/EmberSaveGame.h"
#include "EmberGameInstance.generated.h"

class UAudioSubsystem;
class ULevelSubsystem;
class UDungeonSubsystem;
class UUserWidget;
class UEmberLoadingWidget;

UCLASS()
class PROJECTEMBER_API UEmberGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	UFUNCTION(BlueprintCallable)
	void TestPlaySound();

	UFUNCTION(BlueprintCallable)
	void SaveVideoSettingsWithEMS(const FEmberVideoSettings& Settings);

	UFUNCTION(BlueprintCallable)
	FEmberVideoSettings LoadVideoSettingsWithEMS();

	UFUNCTION(BlueprintCallable)
	void SaveAudioSettingsWithEMS(const FEmberAudioSettings& Settings);

	UFUNCTION(BlueprintCallable)
	FEmberAudioSettings LoadAudioSettingsWithEMS();

	UFUNCTION(BlueprintCallable)
	void RequestOpenLevel(FName MapName);

	UFUNCTION(BlueprintCallable)
	void TestPlaySFX(ESfxSoundType SoundType, const FName RowName, FVector Location = FVector::ZeroVector);
	
	UPROPERTY(BlueprintReadWrite)
	TArray<FEmberKeyMappingEntry> SavedMappings;

	UFUNCTION(BlueprintCallable)
	void ApplySavedMoveBindingsToUserSettings();

	UFUNCTION(BlueprintCallable)
	void ApplySavedActionKeyMappingsToUserSettings();

	void SaveKeyMappingsWithEMS();

	void LoadKeyMappingsWithEMS();

	UPROPERTY(BlueprintReadWrite)
	TArray<FEmberDirectionalMoveEntry> SavedMoveBindings;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> PlayerMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> UI_ALS_MappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> UIMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	
	UFUNCTION(BlueprintCallable)
	UDungeonSubsystem* GetDungeonSubSystem();

	// 현재 지역 확인용
	EAreaType CurrentAreaType = EAreaType::GrasslandArea;

private:
	UPROPERTY()
	UAudioSubsystem* AudioSubsystem;

	UPROPERTY()
	ULevelSubsystem* LevelSubsystem;

	UPROPERTY()
	UDungeonSubsystem* DungeonSubsystem;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSoftClassPtr<UUserWidget> LoadingScreenClass;

	UPROPERTY()
	UUserWidget* LoadingScreenWidget;

	FStreamableManager AssetLoader;
};
