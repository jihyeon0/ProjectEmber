#pragma once

#include "CoreMinimal.h"
#include "EnumSet.h"
#include "GameInstance/Structs/SoundDataArrayStruct.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "EmberLog/EmberLog.h"
#include "AudioSubsystem.generated.h"

class USoundBase;
class UAudioDataSettings;

UCLASS()
class PROJECTEMBER_API UAudioSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	void LoadDataTables();

	void PlayBGM(EAreaSoundType SoundType);

	UFUNCTION(Blueprintable)
	void PlaySFX(ESfxSoundType SoundType, const FName RowName, FVector Location = FVector::ZeroVector);

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void SetAndApplyMasterVolume(float NewVolume);

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void SetBgmVolume(float VolumeValue);

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void SetEffectsVolume(float VolumeValue);

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void SetUIVolume(float VolumeValue);

	UFUNCTION(BlueprintCallable, Category = "Audio")
	float GetMasterVolume() const;

	UFUNCTION(BlueprintCallable, Category = "Audio")
	float GetBgmVolume() const;

	UFUNCTION(BlueprintCallable, Category = "Audio")
	float GetEffectsVolume() const;

	UFUNCTION(BlueprintCallable, Category = "Audio")
	float GetUIVolume() const;

	void PlayBGMSoundByArea(EAreaType Type);
	void PlayBGMSound(EAreaSoundType Type);
	
	bool CheckValidOfBgmSource(EAreaSoundType SoundType);
	
	bool CheckValidOfBgmAudio();
	//bool CheckValidOfUIAudio();
	bool CheckValidOfCharacterAudio();
	//bool CheckValidOfMonsterAudio();
	
	template<typename StructType>
	void PlaySFXByRowName(UObject* WorldContext, UDataTable* Table, const FName RowName, FVector Location)
	{
		if (Table)
		{
			const StructType* FoundRow = Table->FindRow<StructType>(RowName, TEXT("PlaySFXByType"));

			if (FoundRow && !FoundRow->Sound.IsNull())
			{
				USoundBase* Sound = FoundRow->Sound.LoadSynchronous();

				if (Sound && WorldContext)
				{
					if (Location.IsZero())
					{
						// UI
						UGameplayStatics::PlaySound2D(WorldContext, Sound, MasterVolume * UIVolume);
						EMBER_LOG(LogTemp, Warning, TEXT("Play 2D Sound"), MasterVolume * UIVolume);
					}
					else
					{
						UGameplayStatics::PlaySoundAtLocation(WorldContext, Sound, Location, MasterVolume * EffectsVolume);
						EMBER_LOG(LogTemp, Warning, TEXT("Play 3D Sound"));
						//ȯ���� ������
					}
				}
				else
				{
					EMBER_LOG(LogTemp, Warning, TEXT("Sound or WorldContext is NULL"));
				}
			}
			else
			{
				EMBER_LOG(LogTemp, Warning, TEXT("Found Row is NULL"));
			}
		}
		else
		{
			EMBER_LOG(LogTemp, Warning, TEXT("SFX Table or EnumPtr is NULL"));
		}
	}

private:
	UPROPERTY()
	FSoundDataArrayStruct SoundDataArraySet;

	UPROPERTY()
	TMap<EAreaSoundType, USoundBase*> BgmSoundMap;

	//UPROPERTY()
	//TMap<EUISfxSoundType, USoundBase*> UISoundMap;

	UPROPERTY()
	UDataTable* AreaSoundTable;

	UPROPERTY()
	UDataTable* CharacterSoundTable;

	UPROPERTY()
	UDataTable* UISfxSoundTable;

	UPROPERTY()
	TObjectPtr<UAudioComponent> BgmComp;

	UPROPERTY()
	const UAudioDataSettings* AudioDataSettings;

	UPROPERTY()
	float MasterVolume = 1.0f;

	UPROPERTY()
	float BgmVolume = 0.5f;

	UPROPERTY()
	float EffectsVolume = 1.0f;

	UPROPERTY()
	float UIVolume = 1.0f;

};
