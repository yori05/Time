// Property of Florian Hulin, shouldn't be used without my consent.


#include "Component/TimeManipulator/TimeManipulatorComponent_Basic.h"

#include "Engine/World.h"
#include "Component/TimeManipulator/Manager_TMComponent_Basic.h"
#include "GameFramework/GameMode.h"

	/**-----------------	Constructor Part		-----------------*/

// Sets default values for this component's properties
UTimeManipulatorComponent_Basic::UTimeManipulatorComponent_Basic()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

}

/**-----------------	Component Function Part		-----------------*/

// Called when the game starts
void UTimeManipulatorComponent_Basic::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	RequestLinkToManager();
}


// Called every frame
void UTimeManipulatorComponent_Basic::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	
}

// Called when the game end
void UTimeManipulatorComponent_Basic::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	//	...

	RemoveLinkToManager();
}

/**-----------------	Management Function Part		-----------------*/

UManager_TMComponent_Basic* UTimeManipulatorComponent_Basic::AccessManagerRef()
{
	if (!IsValid(ManagerRef))
	{
		auto World = GetWorld();

		if (IsValid(World))
		{
			auto GM = World->GetAuthGameMode();

			if (IsValid(GM))
			{
				ManagerRef = GM->GetComponentByClass<UManager_TMComponent_Basic>();
			}
		}

	}

	return ManagerRef;
}

void UTimeManipulatorComponent_Basic::RequestLinkToManager()
{
	auto TM = AccessManagerRef();

	if (IsValid(TM))
	{
		TM->RequestAdd(this);
	}
}

void UTimeManipulatorComponent_Basic::RemoveLinkToManager()
{
	auto TM = AccessManagerRef();

	if (IsValid(TM))
	{
		TM->RequestRemove(this);
	}
}

void UTimeManipulatorComponent_Basic::ForceDown()
{
	bForcedDown = true;
}

void UTimeManipulatorComponent_Basic::LiberateAuthority()
{
	bForcedDown = false;
}

// Link this component to the manager's callback
void UTimeManipulatorComponent_Basic::LinkToCallback()
{
	if (IsValid(ManagerRef))
	{
		if (bForcedDown || !bSelfAuthority)
		{
			ManagerRef->OnTimeUpdated.AddUniqueDynamic(this, &UTimeManipulatorComponent_Basic::UpdateTimeByManager);
			ManagerRef->OnStepMade.AddUniqueDynamic(this, &UTimeManipulatorComponent_Basic::CallStepMadeByManager);
		}

		ManagerRef->OnActivateRecordState.AddUniqueDynamic(this, &UTimeManipulatorComponent_Basic::ChangeToRecordState);
		ManagerRef->OnActivateStopState.AddUniqueDynamic(this, &UTimeManipulatorComponent_Basic::ChangeToStopState);
		ManagerRef->OnActivateReplayState.AddUniqueDynamic(this, &UTimeManipulatorComponent_Basic::ChangeToReplayState);
	}
}

// Remove the link to this component and to the manager's callback
void UTimeManipulatorComponent_Basic::BreakLinkToCallback()
{
	if (IsValid(ManagerRef))
	{
		if (ManagerRef->OnTimeUpdated.IsAlreadyBound(this, &UTimeManipulatorComponent_Basic::UpdateTimeByManager))
		{
			ManagerRef->OnTimeUpdated.RemoveDynamic(this, &UTimeManipulatorComponent_Basic::UpdateTimeByManager);
		}
		if (ManagerRef->OnStepMade.IsAlreadyBound(this, &UTimeManipulatorComponent_Basic::CallStepMadeByManager))
		{
			ManagerRef->OnStepMade.RemoveDynamic(this, &UTimeManipulatorComponent_Basic::CallStepMadeByManager);
		}

		if (ManagerRef->OnActivateRecordState.IsAlreadyBound(this, &UTimeManipulatorComponent_Basic::ChangeToRecordState))
		{
			ManagerRef->OnActivateRecordState.RemoveDynamic(this, &UTimeManipulatorComponent_Basic::ChangeToRecordState);
		}
		if (ManagerRef->OnActivateStopState.IsAlreadyBound(this, &UTimeManipulatorComponent_Basic::ChangeToStopState))
		{
			ManagerRef->OnActivateStopState.RemoveDynamic(this, &UTimeManipulatorComponent_Basic::ChangeToStopState);
		}
		if (ManagerRef->OnActivateReplayState.IsAlreadyBound(this, &UTimeManipulatorComponent_Basic::ChangeToReplayState))
		{
			ManagerRef->OnActivateReplayState.RemoveDynamic(this, &UTimeManipulatorComponent_Basic::ChangeToReplayState);
		}

	}
}

void UTimeManipulatorComponent_Basic::SynchroniseWitchManager()
{
	if (IsValid(ManagerRef))
	{
		TimeSaved = ManagerRef->GetTimeSaved();
		TimeElapsed = ManagerRef->GetTimeElapsed();
		bStepMade = ManagerRef->GetStepMade();
		TMState_Current = ManagerRef->GetTimeManipulatorState();
	}
}

/**-----------------	Time Evolution Function Part		-----------------*/
/**======	Time Parameter Part		======*/

// Verification if update time can function, this component have to be self autority
bool UTimeManipulatorComponent_Basic::CanUpdateTime()
{
	return Super::CanUpdateTime() && bSelfAuthority && !bForcedDown;
}

// Update the Times on this component, dependent of @OnTimeUpdate of the Manager Time Manipulator Component
void UTimeManipulatorComponent_Basic::UpdateTimeByManager(float _DeltaTime)
{
	if (IsValid(ManagerRef))
	{
		TimeSaved = ManagerRef->GetTimeSaved();
		TimeElapsed = ManagerRef->GetTimeElapsed();
		bStepMade = ManagerRef->GetStepMade();
		OnTimeUpdated.Broadcast(_DeltaTime);
	}
}

/**======	Step Action Part		======*/

bool UTimeManipulatorComponent_Basic::CanStepMade()
{
	return Super::CanStepMade() && bSelfAuthority && !bForcedDown;
}

void UTimeManipulatorComponent_Basic::CallStepMadeByManager()
{
	StepMade();
	BP_StepMade();
	OnStepMade.Broadcast();
}