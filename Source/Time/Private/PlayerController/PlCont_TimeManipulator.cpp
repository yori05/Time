// Property of Florian Hulin, shouldn't be used without my consent.


#include "PlayerController/PlCont_TimeManipulator.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/World.h"
#include "GameMode/GameMode_Basic.h"
#include "Component/TimeManipulator/Manager_TMComponent_Basic.h"


DEFINE_LOG_CATEGORY(LogPlayerControllerTM);

/**-----------------	Inherit Function Part		-----------------*/

void APlCont_TimeManipulator::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	// Set up action bindings
	if (IsValid(EnhancedInputComponent))
	{
		EnhancedInputComponent->BindAction(BackwardTimeAction, ETriggerEvent::Started, this, &APlCont_TimeManipulator::ReduceTime);
		EnhancedInputComponent->BindAction(ForwardTimeAction, ETriggerEvent::Started, this, &APlCont_TimeManipulator::IncraseTime);

	}

}

void APlCont_TimeManipulator::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* World = GetWorld())
	{
		if (AGameModeBase* GM = World->GetAuthGameMode())
		{
			if (UManager_TMComponent_Basic* TMMana = GM->GetComponentByClass<UManager_TMComponent_Basic>())
			TM_ManagerRef = TMMana;
		}
	}

}

/**-----------------	Input Function Part		-----------------*/

void APlCont_TimeManipulator::MakeBackwardTime()
{
	if (CanBackwardTime())
	{
		if (IsValid(TM_ManagerRef))
		{
			TM_ManagerRef->LaunchReplayState();
		}
	}
}

bool APlCont_TimeManipulator::CanBackwardTime()
{
	if (IsValid(TM_ManagerRef))
	{
		return TM_ManagerRef->CanLaunchReplayState();
	}

	return false;
}

void APlCont_TimeManipulator::MakeForwardTime()
{
	if (CanForwardTime())
	{
		if (IsValid(TM_ManagerRef))
		{
			TM_ManagerRef->LaunchRecordState();
		}
	}
}


bool APlCont_TimeManipulator::CanForwardTime()
{
	if (IsValid(TM_ManagerRef))
	{
		return TM_ManagerRef->CanLaunchRecordState();
	}

	return false;
}

void APlCont_TimeManipulator::ReduceTime()
{
	if (CanReduceTime())
	{
		if (IsValid(TM_ManagerRef))
		{
			if (TM_ManagerRef->IsInHoldState())
			{
				TM_ManagerRef->LaunchReplayState();
			}
			else
			{
				TM_ManagerRef->LaunchStopState();
			}
		}
	}
}

bool APlCont_TimeManipulator::CanReduceTime()
{
	if (IsValid(TM_ManagerRef))
	{
		return !TM_ManagerRef->IsInReplayState() && (TM_ManagerRef->CanLaunchReplayState() || TM_ManagerRef->CanLaunchStopState());
	}

	return false;
}

void APlCont_TimeManipulator::IncraseTime()
{
	if (CanIncraseTime())
	{
		if (IsValid(TM_ManagerRef))
		{
			if (TM_ManagerRef->IsInHoldState())
			{
				TM_ManagerRef->LaunchRecordState();
			}
			else
			{
				TM_ManagerRef->LaunchStopState();
			}
		}
	}
}

bool APlCont_TimeManipulator::CanIncraseTime()
{
	if (IsValid(TM_ManagerRef))
	{
		return !TM_ManagerRef->IsInRecordState() && (TM_ManagerRef->CanLaunchRecordState() || TM_ManagerRef->CanLaunchStopState());
	}

	return false;
}
