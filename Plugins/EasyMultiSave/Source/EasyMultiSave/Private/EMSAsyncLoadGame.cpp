//Easy Multi Save - Copyright (C) 2025 by Michael Hegemann.  

#include "EMSAsyncLoadGame.h"
#include "EMSFunctionLibrary.h"
#include "EMSObject.h"
#include "Engine/Engine.h"
#include "Modules/ModuleManager.h"
#include "Async/Async.h"
#include "UObject/UObjectIterator.h"

/**
Init
**/

UEMSAsyncLoadGame::UEMSAsyncLoadGame(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, Mode(ESaveGameMode::MODE_All)
	, Data(0)
	, bIsActive(false)
	, bLoadFailed(false)
	, bFullReload(false)
	, bAutoLoadLevel(false)
	, LoadedActorNum(0) {}

UEMSAsyncLoadGame* UEMSAsyncLoadGame::AsyncLoadActors(UObject* WorldContextObject, int32 Data, bool bFullReload)
{
	if (UEMSObject* EMSObject = UEMSObject::Get(WorldContextObject))
	{
		const ESaveGameMode Mode = FAsyncSaveHelpers::GetMode(Data);

		if (EMSObject->IsAsyncSaveOrLoadTaskActive(Mode))
		{
			return nullptr;
		}

		UEMSAsyncLoadGame* LoadTask = NewObject<UEMSAsyncLoadGame>(GetTransientPackage());		
		if(LoadTask)
		{
			LoadTask->EMS = EMSObject;
			LoadTask->Data = Data;
			LoadTask->Mode = Mode;
			LoadTask->bFullReload = bFullReload;
			return LoadTask;
		}
	}

	return nullptr;
}

void UEMSAsyncLoadGame::AutoLoadLevelActors(UEMSObject* EMSObject)
{
	UEMSAsyncLoadGame* LoadTask = NewObject<UEMSAsyncLoadGame>(GetTransientPackage());
	if (LoadTask)
	{
		LoadTask->EMS = EMSObject;
		LoadTask->Data = ENUM_TO_FLAG(ELoadTypeFlags::LF_Level);
		LoadTask->Mode = ESaveGameMode::MODE_Level;
		LoadTask->bFullReload = false;
		LoadTask->bAutoLoadLevel = true;
		LoadTask->RegisterWithGameInstance(EMSObject);
		LoadTask->Activate();
	}
}

void UEMSAsyncLoadGame::Activate()
{
	if (EMS)
	{
		//Fail when still streaming
		if (!bAutoLoadLevel && Data & ENUM_TO_FLAG(ELoadTypeFlags::LF_Level))
		{
			if (EMS->IsLevelStreaming())
			{
				UE_LOG(LogEasyMultiSave, Warning, TEXT("Async load attempt while streaming. To avoid invalid or redundant loading operations, use 'Is Level Streaming Active' to check."));
			}
		}

		bIsActive = true;
		EMS->GetTimerManager().SetTimerForNextTick(this, &UEMSAsyncLoadGame::PreLoading);
	}
}

/**
Load Actors
**/

void UEMSAsyncLoadGame::PreLoading()
{
	if (!EMS)
	{
		return;
	}

	if (Data & ENUM_TO_FLAG(ELoadTypeFlags::LF_Player))
	{
		if (!EMS->HasValidPlayer())
		{
			EMS->GetTimerManager().SetTimerForNextTick(this, &UEMSAsyncLoadGame::PreLoading);
			return;
		}
	}

	if (Data & ENUM_TO_FLAG(ELoadTypeFlags::LF_Level))
	{
		if (!EMS->HasValidGameMode())
		{
			EMS->GetTimerManager().SetTimerForNextTick(this, &UEMSAsyncLoadGame::PreLoading);
			return;
		}
	}

	const EPrepareType PrepareType = bFullReload ? EPrepareType::PT_FullReload : EPrepareType::PT_Default;
	EMS->PrepareLoadAndSaveActors(Data, EAsyncCheckType::CT_Load, PrepareType);

	EMS->GetTimerManager().SetTimerForNextTick(this, &UEMSAsyncLoadGame::StartLoading);

	const float WaitTime = UEMSPluginSettings::Get()->AsyncWaitDelay;
	if (WaitTime > 0.f)
	{
		EMS->GetTimerManager().SetTimer(FailedTimerHandle, FTimerDelegate::CreateUObject(this, &UEMSAsyncLoadGame::FailLoadingTask), WaitTime, false);
	}
}

void UEMSAsyncLoadGame::ClearFailTimer()
{
	if (EMS)
	{
		if (FailedTimerHandle.IsValid())
		{
			EMS->GetTimerManager().ClearTimer(FailedTimerHandle);
		}
	}
}

void UEMSAsyncLoadGame::StartLoading()
{
	if (EMS)
	{
		EMS->GetTimerManager().SetTimerForNextTick(this, &UEMSAsyncLoadGame::PreparePlayer);
	}
}

void UEMSAsyncLoadGame::PreparePlayer()
{
	bLoadFailed = true;

	if (!EMS)
	{
		return;
	}

	if (Data & ENUM_TO_FLAG(ELoadTypeFlags::LF_Player))
	{
		if (EMS->TryLoadPlayerFile())
		{
			SetLoadNotFailed();
			EMS->GetTimerManager().SetTimerForNextTick(this, &UEMSAsyncLoadGame::LoadPlayer);
			return;
		}
	}

	EMS->GetTimerManager().SetTimerForNextTick(this, &UEMSAsyncLoadGame::LoadLevel);
}

void UEMSAsyncLoadGame::LoadPlayer()
{
	if (EMS)
	{
		EMS->LoadPlayerActors(EMS->GetPlayerController());
		EMS->GetTimerManager().SetTimerForNextTick(this, &UEMSAsyncLoadGame::LoadLevel);
	}
}

void UEMSAsyncLoadGame::LoadLevel()
{ 
	if (!EMS)
	{
		return;
	}

	if (Data & ENUM_TO_FLAG(ELoadTypeFlags::LF_Level))
	{
		if (EMS->TryLoadLevelFile())
		{
			SetLoadNotFailed();
			EMS->GetTimerManager().SetTimerForNextTick(this, &UEMSAsyncLoadGame::LoadGameMode);
		}
		else
		{
			FinishLoading();
		}
	}
	else
	{
		FinishLoading();
	}
}

void UEMSAsyncLoadGame::LoadGameMode()
{
	if (EMS)
	{
		EMS->LoadGameMode();
		EMS->GetTimerManager().SetTimerForNextTick(this, &UEMSAsyncLoadGame::LoadLevelScripts);
	}
}

void UEMSAsyncLoadGame::LoadLevelScripts()
{
	if (EMS)
	{
		EMS->LoadLevelScripts();
		EMS->GetTimerManager().SetTimerForNextTick(this, &UEMSAsyncLoadGame::PrepareLevelActors);
	}
}

void UEMSAsyncLoadGame::PrepareLevelActors()
{
	if (EMS)
	{
		if (EMS::ArrayEmpty(EMS->GetSavedActors()))
		{
			FinishLoading();
			return;
		}

		EMS->PrepareLevelActors();
		EMS->GetTimerManager().SetTimerForNextTick(this, &UEMSAsyncLoadGame::LoadLevelActors);
	}
}

void UEMSAsyncLoadGame::LoadLevelActors()
{
	if (EMS)
	{
		EMS->LoadLevelActors(this);
	}
}

/**
Deferred Loading
**/

void UEMSAsyncLoadGame::StartDeferredLoad()
{
	if (EMS)
	{
		SavedActors = EMS->GetPrunedLevelActors();
		DeferredLoadActors();
	}
}

void UEMSAsyncLoadGame::DeferredLoadActors()
{
	if (!EMS || !bIsActive)
	{
		return;
	}

	const uint32 Batch = UEMSPluginSettings::Get()->DeferredLoadStackSize;
	uint32 LoadNum = 0;

	if (LoadedActorNum >= SavedActors.Num())
	{
		FinishLoading();
		return;
	}

	while (LoadNum < Batch)
	{
		const int32 FullBatch = LoadNum + LoadedActorNum;
		if (FullBatch >= SavedActors.Num())
		{
			break;
		}

		const uint32 MinLoadNum = FMath::Min(FullBatch, SavedActors.Num() - 1);
		EMS->SpawnOrUpdateLevelActor(SavedActors[MinLoadNum]);
		LoadNum++;
	}

	LoadedActorNum += Batch;
	EMS->GetTimerManager().SetTimerForNextTick(this, &UEMSAsyncLoadGame::DeferredLoadActors);
}

/**
Finish
**/

void UEMSAsyncLoadGame::FinishLoading()
{
	//Has to be a tick before broadcast.
	bIsActive = false;
	ClearFailTimer();

	if (!EMS)
	{
		SetReadyToDestroy();
		return;
	}

	if (Data & ENUM_TO_FLAG(ELoadTypeFlags::LF_Level))
	{
		EMS->FinishLoadingLevel(!bLoadFailed);
	}

	if (bLoadFailed)
	{
		EMS->GetTimerManager().SetTimerForNextTick(this, &UEMSAsyncLoadGame::FailLoadingTask);
	}
	else
	{
		EMS->GetTimerManager().SetTimerForNextTick(this, &UEMSAsyncLoadGame::CompleteLoadingTask);
	}
}

void UEMSAsyncLoadGame::ForceDestroy()
{
	bIsActive = false;
	SetReadyToDestroy();
}

void UEMSAsyncLoadGame::CompleteLoadingTask()
{
	OnCompleted.Broadcast();
	SetReadyToDestroy();
}

void UEMSAsyncLoadGame::FailLoadingTask()
{
	OnFailed.Broadcast();
	SetReadyToDestroy();
}

void UEMSAsyncLoadGame::FinishTaskThreadSafe(const TWeakObjectPtr<UEMSAsyncLoadGame> InTask)
{
	if (!InTask.IsValid())
	{
		return;
	}

	auto FinishLoadingTask = [InTask]()
	{
		UEMSAsyncLoadGame* NewLoadTask = InTask.Get();
		if (IsValid(NewLoadTask))
		{
			NewLoadTask->FinishLoading();
		}
	};

	//This fixes a potential crash in PIE, when stopping play while multi-thread loading is not finished.
	if (!IsInGameThread())
	{
		AsyncTask(ENamedThreads::GameThread, [FinishLoadingTask]()
		{
			FinishLoadingTask();
		});
	}
	else
	{
		FinishLoadingTask();
	}
}
