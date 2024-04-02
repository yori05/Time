// Property of Florian Hulin, shouldn't be used without my consent.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enum/TimeManipulatorEnum.h"

#include "Base_TimeManipulatorComponent.generated.h"

/**-----------------	Delegate definition Part		-----------------*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBaseTMEventSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBaseTMFloatEventSignature, float, _DeltaTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBaseTMStateEventSignature, ETimeManipulatorState, _NewState);

/**
*  Base Time Manipulator Component
* Part of the Time Manipulator system
* 
* Base for A time manipulator component and / or his manager
* In case you want to create a Time Manipulator Component with basic function should use @TimeManipulatorComponent_Basic
* In case you want to create a Manager Time Manipulator Component with basic function should use @Manager_TMComponent_Basic
* 
* This function keep the most basic and common function between a TM Component and the Manager
* 
* * This component handle :
* -> Time saved by it
* -> Time step when a new tick for record of the curve is launch
* -> Time elapsed between two steps
* -> Time State, and the state machine to perform it
* 
*/
UCLASS( ClassGroup=(TimeManipulator), Abstract)
class TIME_API UBase_TimeManipulatorComponent : public UActorComponent
{
	GENERATED_BODY()

	/**-----------------	Variable Part		-----------------*/
	/**======	Time Variable Part		======*/
protected:

	/**
	*  Time Saved :
	* Represent the time tracking by this component, used to record / replay variation using this value on a curve
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (AllowPrivateAccess = "true"))
	float TimeSaved = 0.f;

	/**
	*  Time Step :
	* Represent the step between to record on curve used by this component, should appear a the delta time between two point of record
	* The smaller is this number, the more precise is the record, but a number too big will add a huge stain on performance.
	*
	* The default value of 0.05f represente 50 millisecond between two record, meaning 20 record by second
	* Note that it won't be able to goes under the time between two tick of this component
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (AllowPrivateAccess = "true"))
	float TimeStep = 0.05f;

	/**
	*  Time Elapsed :
	* Represent the time elapsed after the last record
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (AllowPrivateAccess = "true"))
	float TimeElapsed = 0.f;

	/**
	* bIncrementByStep :
	* Define if the Times on this component should be updated by Step or Raw
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Activity", meta = (AllowPrivateAccess = "true"))
	bool bIncrementByStep = true;

	/**
	* bStepMade :
	* Define if the a Step has been made by the @TimeElapsed :
	* - Will activate no matter the value of @bIncrementByStep
	* - Will activate if the TMState is set as forward or backward
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (AllowPrivateAccess = "true"))
	bool bStepMade = true;


	/**======	Time Manipulator State Part		======*/
protected:

	/**
	* TMState_Current :
	* Keep the TimeManipulatorState, is define by the manager
	* Record of the current Time Manipulator State
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeState", meta = (AllowPrivateAccess = "true"))
	ETimeManipulatorState TMState_Current = ETimeManipulatorState::TMS_Forward;

	/**
	* TMState_Previous :
	* Keep the TimeManipulatorState, is define by the manager
	* Record of the Previous TMState usefull in case the time manipulator state is in transition
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimeState", meta = (AllowPrivateAccess = "true"))
	ETimeManipulatorState TMState_Previous = ETimeManipulatorState::TMS_Forward;


/**======	Time Manipulator State Part		======*/
public:

	///**
	//*  Test parameter :
	//* Parameter used to test thing
	//*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test", meta = (AllowPrivateAccess = "true"))
	//int32 TestParam = 0;


	/**-----------------	Callback Part		-----------------*/
public:

	/**======	TMState Part		======*/

	//Called when the time manipulator state change
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FBaseTMStateEventSignature OnChangeState;

	//Called when activate record is called
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FBaseTMEventSignature OnActivateRecordState;

	//Called when on the tick of the record state
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FBaseTMFloatEventSignature OnTickRecord;

	//Called when activate stop is called
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FBaseTMEventSignature OnActivateStopState;

	//Called when on the tick of the stop state
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FBaseTMFloatEventSignature OnTickStop;

	//Called when the replay state is activated
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FBaseTMEventSignature OnActivateReplayState;

	//Called when on the tick of the replay state
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FBaseTMFloatEventSignature OnTickReplay;
	
	/**======	Time Part		======*/

	//Called when Step Made is called
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FBaseTMFloatEventSignature OnTimeUpdated;

	//Called when Step Made is called
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FBaseTMEventSignature OnStepMade;

	/**-----------------	Lambda Part		-----------------*/
protected:

	//Function pointer to call the current perform state function 
	TFunction<void(float _DeltaTime)> PerformStateFunction;

	/**-----------------	Constructor Part		-----------------*/
public:

	// Sets default values for this component's properties
	UBase_TimeManipulatorComponent();

	/**-----------------	Component Function Part		-----------------*/
protected:

	// Called when the game starts
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Called when the game end
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	/**-----------------	Time Evolution Function Part		-----------------*/
	/**======	Time Parameter Part		======*/
protected:

	/**
	* Will call the update time function on this component.
	* Will choose between UpdateTimeRaw or UpdateTimeByStep using @bIncrementByStep
	*/
	UFUNCTION(BlueprintCallable)
	virtual void CallUpdateTime(float _DeltaTime);

	/**
	*  Verification if @CallUpdateTime can function
	*/
	UFUNCTION(BlueprintCallable)
	virtual bool CanUpdateTime();

	/**
	* Update Times for this component
	* Update @TimeSaved at the same time as @TimeElapsed
	* Add / Out @_DeltaTime to @TimeElapsed until he is egal to @TimeStep or zero in case time is reversed (@bReverse)
	* In case @TimeElasped satisfy on this condition @HasAStep or @HasAReverseStep is set as true
	*
	*/
	UFUNCTION(BlueprintCallable)
	virtual void UpdateTimeRaw(float _DeltaTime);

	/**
	* Update Times for this component
	* Update @TimeSaved in case @TimeElapsed one of this condition by @TimeStep
	* Add / Out @_DeltaTime to @TimeElapsed until he is egal to @TimeStep or zero in case time is reversed (@bReverse)
	* In case @TimeElapsed satisfy one of this condition @HasAStep or @HasAReverseStep is set as true
	*
	*/
	UFUNCTION(BlueprintCallable)
	virtual void UpdateTimeByStep(float _DeltaTime);

	/**======	Step Action Part		======*/
protected:

	/**
	* Call the action in case :
	* - @bStepMade is true
	* - @bHasAutority is false, meaning that it was the manager that called it
	* - @bForcedDown is true, meaning that it was the manager that called it
	*
	* If one on theses conditions are true will call the function got @StepMade() in C++ and BP as well as the event OnStepMade
	* after what @bStepMade will be set as false
	*
	*/
	UFUNCTION(BlueprintCallable)
	virtual void CallStepMade();

	/** 
	*  Verification if @CallStepMade can function
	*/
	UFUNCTION(BlueprintCallable)
	virtual bool CanStepMade();

	/**
	* Action take when @bStepMade is validate
	* Use C++
	*
	* Called by CallStepMade
	*
	*/
	virtual void StepMade();

	/**
	* Action take when @bStepMade is validate
	* Use BP
	*
	* Called by CallStepMade
	*
	*/
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "StepMade"))
	void BP_StepMade();

	/**-----------------	Time Manipulator State Function Part		-----------------*/
	/**======	Changing State Part		======*/

protected:

	/**
	*  Will change the state to the new one
	* Will use @CanChangeTMState to verify if it's doable
	*/
	UFUNCTION(BlueprintCallable)
	virtual void ChangeTMState(ETimeManipulatorState _NewState);

	/**
	*  Verification if the state can be change to the new one
	*/
	UFUNCTION(BlueprintCallable)
	virtual bool CanChangeTMState(ETimeManipulatorState _NewState);

	/**
	*  Will change the state to record state
	*/
	UFUNCTION(BlueprintCallable)
	virtual void ChangeToRecordState();

	/**
	*  Will change the state to stop state
	*/
	UFUNCTION(BlueprintCallable)
	virtual void ChangeToStopState();

	/**
	*  Will change the state to replay state
	*/
	UFUNCTION(BlueprintCallable)
	virtual void ChangeToReplayState();

	/**======	Call State Part		======*/

protected:

	/**>> Record Part <<**/

	/**
	*  Call Record State
	* Will be called by the change state function
	* Begininng of this state will call implementation functions and callback in this order
	* Currently used when the time is set as Forward
	*/
	UFUNCTION(BlueprintCallable)
	virtual void CallActivateRecordState();

	/**
	*  Record State
	* Gameplay implementation function in c++ can be override to add mechanics if wanted
	* Currently used when the time is set as Forward
	*/
	virtual void ActivateRecordState();

	/**
	*  Record State
	* Gameplay implementation function in blueprint can be override in blueprint to add mechanics if wanted
	* Currently used when the time is set as Forward
	*/
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ActivateRecordState"))
	void BP_ActivateRecordState();

	/**>> Stop Part <<**/

	/**
	*  Call Stop State
	* Will be called by the change state function
	* Begininng of this state will call implementation functions and callback in this order
	* Currently used when the time is set as Hold
	*/
	UFUNCTION(BlueprintCallable)
	virtual void CallActivateStopState();

	/**
	*  Stop State
	* Gameplay implementation function in c++ can be override to add mechanics if wanted
	* Currently used when the time is set as Hold
	*/
	virtual void ActivateStopState();

	/**
	*  Stop State
	* Gameplay implementation function in blueprint can be override in blueprint to add mechanics if wanted
	* Currently used when the time is set as Hold
	*/
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ActivateStopState"))
	void BP_ActivateStopState();

	/**>> Replay Part <<**/

	/**
	*  Call Replay State
	* Will be called by the change state function
	* Begininng of this state will call implementation functions and callback in this order
	* Currently used when the time is set as Backward
	*/
	UFUNCTION(BlueprintCallable)
	virtual void CallActivateReplayState();

	/**
	*  Replay State
	* Gameplay implementation function in c++ can be override to add mechanics if wanted
	* Currently used when the time is set as Backward
	*/
	virtual void ActivateReplayState();

	/**
	*  Replay State
	* Gameplay implementation function in blueprint can be override in blueprint to add mechanics if wanted
	* Currently used when the time is set as Backward
	*/
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "ActivateReplayState"))
	void BP_ActivateReplayState();

	/**======	Perform State Part		======*/
protected:

	/**
	*  Perform record state
	* Call the action take on the tick by this component on this step
	* Currently used when the time is set as Forward
	*/
	UFUNCTION(BlueprintCallable)
	virtual void PerformRecordState(float _DeltaTime);

	/**
	*  Perform record state
	* Action take on the tick of the component on this step
	* Currently used when the time is set as Forward
	*/
	virtual void TickRecordState(float _DeltaTime);

	/**
	*  BP Perform record state
	* Action take on the tick of the component on this step
	* Blueprint implementable event
	* Currently used when the time is set as Forward
	*/
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "TickRecordState"))
	void BP_TickRecordState(float _DeltaTime);

	/**
	*  Perform Stop state
	* Call the action take on the tick by this component on this step
	* Currently used when the time is set as Hold
	*/
	UFUNCTION(BlueprintCallable)
	virtual void PerformStopState(float _DeltaTime);

	/**
	*  Perform Stop state
	* Action take on the tick of the component on this step
	* Currently used when the time is set as Hold
	*/
	virtual void TickStopState(float _DeltaTime);

	/**
	*  BP Perform Stop state
	* Action take on the tick of the component on this step
	* Blueprint implementable event
	* Currently used when the time is set as Hold
	*/
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "TickStopState"))
	void BP_TickStopState(float _DeltaTime);

	/**
	*  Perform Replay state
	* Call the action take on the tick by this component on this step
	* Currently used when the time is set as Backward
	*/
	UFUNCTION(BlueprintCallable)
	virtual void PerformReplayState(float _DeltaTime);

	/**
	*  Perform Replay state
	* Action take on the tick of the component on this step
	* Currently used when the time is set as Backward
	*/
	virtual void TickReplayState(float _DeltaTime);

	/**
	*  BP Perform Replay state
	* Action take on the tick of the component on this step
	* Blueprint implementable event
	* Currently used when the time is set as Backward
	*/
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "TickReplayState"))
	void BP_TickReplayState(float _DeltaTime);


	/**-----------------	Accessor Part		-----------------*/
public:

	FORCEINLINE ETimeManipulatorState GetTimeManipulatorState() { return TMState_Current; };
	FORCEINLINE float GetTimeSaved() { return TimeSaved; };
	FORCEINLINE float GetTimeElapsed() { return TimeElapsed; };
	FORCEINLINE float GetTimeStep() { return TimeStep; };
	FORCEINLINE bool GetStepMade() { return bStepMade; };
};
