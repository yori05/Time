// Property of Florian Hulin, shouldn't be used without my consent.

#include "Component/TimeManipulator/Base_TimeManipulatorComponent.h"

/**-----------------	Constructor Part		-----------------*/

// Sets default values for this component's properties
UBase_TimeManipulatorComponent::UBase_TimeManipulatorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...


	ComponentTags.Add(TEXT("TimeManipulator"));

	switch (TMState_Current)
	{
	case ETimeManipulatorState::TMS_Forward:
		PerformStateFunction = [this](float _DeltaTime) {this->PerformRecordState(_DeltaTime); };
		break;
	case ETimeManipulatorState::TMS_Hold:
		PerformStateFunction = [this](float _DeltaTime) {this->PerformStopState(_DeltaTime); };
		break;
	case ETimeManipulatorState::TMS_Backward:
		PerformStateFunction = [this](float _DeltaTime) {this->PerformReplayState(_DeltaTime); };
		break;
	default:
		PerformStateFunction = nullptr;
		break;
	}
}

/**-----------------	Component Function Part		-----------------*/

// Called when the game starts
void UBase_TimeManipulatorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	//PerformFunction = [this]() {};
}


// Called every frame
void UBase_TimeManipulatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (CanUpdateTime())
	{
		CallUpdateTime(DeltaTime);

		if (bStepMade)
		{
			CallStepMade();
		}
	}

	if (PerformStateFunction)
	{
		PerformStateFunction(DeltaTime);
	}
}

// Called when the component is destroyed
void UBase_TimeManipulatorComponent::EndPlay(EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// ...

	PerformStateFunction.Reset();

}

/**-----------------	Time Evolution Function Part		-----------------*/
/**======	Time Parameter Part		======*/

// Call the update time function accordly to @bIncrementByStep
void UBase_TimeManipulatorComponent::CallUpdateTime(float _DeltaTime)
{
	if (CanUpdateTime())
	{
		if (bIncrementByStep)
		{
			UpdateTimeByStep(_DeltaTime);
		}
		else
		{
			UpdateTimeRaw(_DeltaTime);
		}

		OnTimeUpdated.Broadcast(_DeltaTime);
	}
}

// Verification for the function CallUpdateTime
bool UBase_TimeManipulatorComponent::CanUpdateTime()
{
	return TMState_Current != ETimeManipulatorState::TMS_Hold;
}

// Update the Times on this component, @TimeSaved and @TimeElapsed are updated as the same time
void UBase_TimeManipulatorComponent::UpdateTimeRaw(float _DeltaTime)
{
	// Incrementation of the time elapsed between two step and of the Time Saved
	TimeSaved += (TMState_Current == ETimeManipulatorState::TMS_Forward ? _DeltaTime : -_DeltaTime);
	TimeElapsed += (TMState_Current == ETimeManipulatorState::TMS_Forward ? _DeltaTime : -_DeltaTime);

	// Verification if a step as been since the last one
	if ((TMState_Current == ETimeManipulatorState::TMS_Forward && TimeElapsed >= TimeStep)
		|| (TMState_Current == ETimeManipulatorState::TMS_Backward && TimeElapsed <= 0.f))
	{
		//Reset of time elapsed
		TimeElapsed -= (TMState_Current == ETimeManipulatorState::TMS_Forward ? TimeStep : -TimeStep);

		// Flag to say a step was made
		bStepMade = true;
	}
}

// Update the Times on this component, @TimeSaved is depend of @TimeElapsed to be updated
void UBase_TimeManipulatorComponent::UpdateTimeByStep(float _DeltaTime)
{
	// Incrementation of the time elapsed between two step
	TimeElapsed += (TMState_Current == ETimeManipulatorState::TMS_Forward ? _DeltaTime : -_DeltaTime);

	// Verification if a step as been since the last one
	if ((TMState_Current == ETimeManipulatorState::TMS_Forward && TimeElapsed >= TimeStep)
		|| (TMState_Current == ETimeManipulatorState::TMS_Backward && TimeElapsed <= 0.f))
	{
		//Incrementation of Time Saved and reset of Time Elapsed
		TimeSaved += (TMState_Current == ETimeManipulatorState::TMS_Forward ? TimeStep : -TimeStep);
		TimeElapsed -= (TMState_Current == ETimeManipulatorState::TMS_Forward ? TimeStep : -TimeStep);

		// Flag to say a step was made
		bStepMade = true;
	}
}

/**======	Step Action Part		======*/

void UBase_TimeManipulatorComponent::CallStepMade()
{
	if (CanStepMade())
	{
		StepMade();
		BP_StepMade();
		OnStepMade.Broadcast();
		bStepMade = false;
	}
}

bool UBase_TimeManipulatorComponent::CanStepMade()
{
	return bStepMade && TMState_Current != ETimeManipulatorState::TMS_Hold;
}

void UBase_TimeManipulatorComponent::StepMade()
{
	//	Add your gameplay action there 
	//	....
}


/**-----------------	Time Manipulator State Function Part		-----------------*/

void UBase_TimeManipulatorComponent::ChangeTMState(ETimeManipulatorState _NewState)
{
	if (CanChangeTMState(_NewState))
	{
		TMState_Previous = TMState_Current;
		TMState_Current = _NewState;

		OnChangeState.Broadcast(_NewState);

		switch (TMState_Current)
		{
		case ETimeManipulatorState::TMS_Forward:
			CallActivateRecordState();
			break;
		case ETimeManipulatorState::TMS_Hold:
			CallActivateStopState();
			break;
		case ETimeManipulatorState::TMS_Backward:
			CallActivateReplayState();
			break;
		default:
			break;
		}
	}
}

bool UBase_TimeManipulatorComponent::CanChangeTMState(ETimeManipulatorState _NewState)
{
	return _NewState != TMState_Current && _NewState != ETimeManipulatorState::TMS_Max;
}

void UBase_TimeManipulatorComponent::ChangeToRecordState()
{
	ChangeTMState(ETimeManipulatorState::TMS_Forward);
}

void UBase_TimeManipulatorComponent::ChangeToStopState()
{
	ChangeTMState(ETimeManipulatorState::TMS_Hold);
}

void UBase_TimeManipulatorComponent::ChangeToReplayState()
{
	ChangeTMState(ETimeManipulatorState::TMS_Backward);
}

/**======	Call State Part		======*/

/**>> Record Part <<**/

void UBase_TimeManipulatorComponent::CallActivateRecordState()
{
	ActivateRecordState();
	BP_ActivateRecordState();
	OnActivateRecordState.Broadcast();
	PerformStateFunction.Reset();
	PerformStateFunction = [this](float _DeltaTime) {this->PerformRecordState(_DeltaTime); };
}

void UBase_TimeManipulatorComponent::ActivateRecordState()
{
	//--- Your gameplay action when record state is activated
}

/**>> Stop Part <<**/

void UBase_TimeManipulatorComponent::CallActivateStopState()
{
	ActivateStopState();
	BP_ActivateStopState();
	OnActivateStopState.Broadcast();
	PerformStateFunction.Reset();
	PerformStateFunction = [this](float _DeltaTime) {this->PerformStopState(_DeltaTime); };
}

void UBase_TimeManipulatorComponent::ActivateStopState()
{
	//--- Your gameplay action when stop state is activated
}

/**>> Replay Part <<**/

void UBase_TimeManipulatorComponent::CallActivateReplayState()
{
	ActivateReplayState();
	BP_ActivateReplayState();
	OnActivateReplayState.Broadcast();
	PerformStateFunction.Reset();
	PerformStateFunction = [this](float _DeltaTime) {this->PerformReplayState(_DeltaTime); };
}

void UBase_TimeManipulatorComponent::ActivateReplayState()
{
	//--- Your gameplay action when replay state is activated
}


/**======	Perform State Part		======*/

void UBase_TimeManipulatorComponent::PerformRecordState(float _DeltaTime)
{
	TickRecordState(_DeltaTime);
	BP_TickRecordState(_DeltaTime);
	OnTickRecord.Broadcast(_DeltaTime);
}

void UBase_TimeManipulatorComponent::TickRecordState(float _DeltaTime)
{
	//--- Action to do by this component on the tick of the record state
}

void UBase_TimeManipulatorComponent::PerformStopState(float _DeltaTime)
{
	TickStopState(_DeltaTime);
	BP_TickStopState(_DeltaTime);
	OnTickStop.Broadcast(_DeltaTime);
}

void UBase_TimeManipulatorComponent::TickStopState(float _DeltaTime)
{
	//--- Action to do by this component on the tick of the Stop state
}

void UBase_TimeManipulatorComponent::PerformReplayState(float _DeltaTime)
{
	TickReplayState(_DeltaTime);
	BP_TickReplayState(_DeltaTime);
	OnTickReplay.Broadcast(_DeltaTime);
}

void UBase_TimeManipulatorComponent::TickReplayState(float _DeltaTime)
{
	//--- Action to do by this component on the tick of the Replay state
}
