// Property of Florian Hulin, shouldn't be used without my consent.

#include "Component/TimeManipulator/Manager_TMComponent_Basic.h"

#include "Component/TimeManipulator/TimeManipulatorComponent_Basic.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"



// Sets default values for this component's properties
UManager_TMComponent_Basic::UManager_TMComponent_Basic()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

}

// Called when the game starts
void UManager_TMComponent_Basic::BeginPlay()
{
	Super::BeginPlay();

	// ...

	if (bSearchTMComps)
	{
		SearchAllTMComps();
	}
}


// Called every frame
void UManager_TMComponent_Basic::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

}

void UManager_TMComponent_Basic::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// ...

	RemoveAllTMComps();
}

/**-----------------	Component Management Part		-----------------*/

bool UManager_TMComponent_Basic::RequestAdd(UTimeManipulatorComponent_Basic* _NewComponent)
{
	if (IsValid(_NewComponent) && !TMComponents.Contains(_NewComponent))
	{
		TMComponents.Add(_NewComponent);

		if (_NewComponent->GetHasSelfAuthority() && ManagerAuthority == EManagerAuthority::MANAGERAUTHORITY_Full)
		{
			_NewComponent->ForceDown();
		}

		if (!IsValid(_NewComponent->GetManagerRef()))
		{
			_NewComponent->ManagerRef = this;
		}
		
		_NewComponent->LinkToCallback();
		_NewComponent->SynchroniseWitchManager();

		return true;
	}

	return false;
}

bool UManager_TMComponent_Basic::RequestRemove(UTimeManipulatorComponent_Basic* _NewComponent)
{
	if (IsValid(_NewComponent) && TMComponents.Contains(_NewComponent))
	{
		TMComponents.Remove(_NewComponent);

		if (_NewComponent->GetIsForcedDown())
		{
			_NewComponent->LiberateAuthority();
		}

		_NewComponent->BreakLinkToCallback();

		_NewComponent->ManagerRef = nullptr;

		return true;
	}

	return false;
}

void UManager_TMComponent_Basic::SearchAllTMComps()
{
	TArray<AActor*> Actors;
	UTimeManipulatorComponent_Basic* TMComp;

	if (UWorld* World = GetWorld())
	{
		UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), Actors);
	}

	for (AActor* Actor : Actors)
	{
		TMComp = nullptr;

		TMComp = Actor->GetComponentByClass<UTimeManipulatorComponent_Basic>();

		if (IsValid(TMComp))
		{
			if (!TMComponents.Contains(TMComp))
			{
				RequestAdd(TMComp);
			}
		}
	}
}

void UManager_TMComponent_Basic::RemoveAllTMComps()
{
	UTimeManipulatorComponent_Basic* TMComp = nullptr;

	while(!TMComponents.IsEmpty())
	{	
		TMComp = TMComponents[0];

		if (IsValid(TMComp))
		{
			RequestRemove(TMComp);
		}
	}
}

/**-----------------	Time Manipulator State Function Part		-----------------*/

void UManager_TMComponent_Basic::LaunchRecordState()
{
	if (CanLaunchRecordState())
	{
		ChangeToRecordState();
	}
}

bool UManager_TMComponent_Basic::CanLaunchRecordState()
{
	return CanChangeTMState(ETimeManipulatorState::TMS_Forward);
}


void UManager_TMComponent_Basic::LaunchStopState()
{
	if (CanLaunchStopState())
	{
		ChangeToStopState();
	}
}


bool UManager_TMComponent_Basic::CanLaunchStopState()
{
	return CanChangeTMState(ETimeManipulatorState::TMS_Hold);
}

void UManager_TMComponent_Basic::LaunchReplayState()
{
	if (CanLaunchReplayState())
	{
		ChangeToReplayState();
	}
}

bool UManager_TMComponent_Basic::CanLaunchReplayState()
{
	return CanChangeTMState(ETimeManipulatorState::TMS_Backward);
}

/**======	Perform State Part		======*/

void UManager_TMComponent_Basic::TickReplayState(float _DeltaTime)
{
	Super::TickReplayState(_DeltaTime);

	if (bChangeAtZero && TimeSaved < 0.f && CanChangeTMState(TMState_AtZero))
	{
		ChangeTMState(TMState_AtZero);
	}
}
