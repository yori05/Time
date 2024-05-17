// Property of Florian Hulin, shouldn't be used without my consent.

/**-----------------	Include		-----------------*/

#include "Component/UWManagerComponent_Basic.h"

#include "Blueprint/UserWidget.h"
#include "GameMode/GameMode_Basic.h"
#include "PlayerController/PlayerController_Basic.h"
#include "Engine/World.h"
#include "Engine/GameInstance.h"

/**-----------------	Constructor Part		-----------------*/

// Sets default values for this component's properties
UUWManagerComponent_Basic::UUWManagerComponent_Basic()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

/**-----------------	Component Function Part		-----------------*/

// Called when the game starts
void UUWManagerComponent_Basic::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	CatchGameMode();
	CatchPlayerController();
	InitializeMapInstances();
}


// Called every frame
void UUWManagerComponent_Basic::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UUWManagerComponent_Basic::CatchGameMode()
{
	GM = GetOwner<AGameModeBase>();

	if (!IsValid(GM))
	{
		auto World = GEngine->GetWorld();

		if (IsValid(World))
		{
			GM = World->GetAuthGameMode();
		}
	}
}

void UUWManagerComponent_Basic::CatchPlayerController()
{
	PC = GetOwner<APlayerController>();

	if (!IsValid(PC))
	{
		auto World = GetWorld();

		if (IsValid(World))
		{
			if (IndexOfThePlayer < World->GetNumPlayerControllers())
			{

				FConstPlayerControllerIterator Iter = World->GetPlayerControllerIterator();

				for (Iter.Reset(); Iter; ++Iter)
				{
					if (Iter.GetIndex() == IndexOfThePlayer)
					{
						PC = Iter->Get();
					}
				}
			}
			else
			{
				PC = World->GetFirstPlayerController();
			}
		}
	}
}

void UUWManagerComponent_Basic::InitializeMapInstances()
{
	if (!UWInstances.IsEmpty())
	{
		for (auto &Instance : UWInstances)
		{
			InitializeFromHelper(Instance.Value);
		}
	}
}

bool UUWManagerComponent_Basic::InitializeFromHelper(FUWManagerHelper& Helper)
{
	if (Helper.bInstanciateOnBP && !IsValid(Helper.Instance))
	{
		if (CreateWidgetFromHelper(Helper))
		{
			if (Helper.bAddToVPOnBP)
			{
				if (AddUWToViewport(Helper))
				{
					if (Helper.bRemoveFromParentOnBP)
					{
						if (RemoveUWFromParent(Helper))
						{
							return true;
						}
	
						return false;
					}
	
					return true;
				}
	
				return false;
			}
	
			return true;
		}
	}

	return false;
}

bool UUWManagerComponent_Basic::CreateWidgetFromHelper(FUWManagerHelper& Helper)
{
	if (IsValid(Helper.Class) && IsValid(PC))
	{
		Helper.Instance = CreateWidget(PC, Helper.Class, *Helper.Name);
	
		if (IsValid(Helper.Instance))
		{
			return true;
		}
	}

	return false;
}

bool UUWManagerComponent_Basic::AddUWToViewport(FUWManagerHelper& Helper)
{
	if (IsValid(Helper.Instance) && !Helper.bIsOnVP)
	{
		Helper.Instance->AddToViewport();
	
		Helper.bIsOnVP = true;
	
		return true;
	}

	return false;
}

bool UUWManagerComponent_Basic::RemoveUWFromParent(FUWManagerHelper& Helper)
{
	if (IsValid(Helper.Instance) && Helper.bIsOnVP)
	{
		Helper.Instance->RemoveFromParent();
	
		Helper.bIsOnVP = false;
	
		return true;
	}

	return false;
}

bool UUWManagerComponent_Basic::RequestInstantiateUW(const FString& UWName)
{
	if (UWInstances.Contains(UWName))
	{
		return CreateWidgetFromHelper(*UWInstances.Find(UWName));
	}

	return false;
}

bool UUWManagerComponent_Basic::RequestAddUWToViewport(const FString& UWName)
{
	if (UWInstances.Contains(UWName))
	{
		return AddUWToViewport(*UWInstances.Find(UWName));
	}

	return false;
}

bool UUWManagerComponent_Basic::RequestRemoveUWFromParent(const FString& UWName)
{
	if (UWInstances.Contains(UWName))
	{
		return RemoveUWFromParent(*UWInstances.Find(UWName));
	}

	return false;
}

bool UUWManagerComponent_Basic::RequestInsertNewUW(const FString& UWName, TSubclassOf<UUserWidget> UWClass, bool bInstantiate, bool bAddToVP, bool bRemoveFromParent)
{
	if (!UWInstances.Contains(UWName))
	{
		FUWManagerHelper* Instance = &UWInstances.Add(UWName);
		Instance->Class = UWClass;
		Instance->Name = UWName;

		if (bInstantiate)
		{
			if (CreateWidgetFromHelper(*Instance))
			{
				if (bAddToVP)
				{
					if (AddUWToViewport(*Instance))
					{
						if (bRemoveFromParent)
						{
							if (RemoveUWFromParent(*Instance))
							{
								return true;
							}

							return false;
						}

						return true;
					}

					return false;
				}

				return true;
			}
		
			return false;
		}

		return true;
	}
	return false;
}
