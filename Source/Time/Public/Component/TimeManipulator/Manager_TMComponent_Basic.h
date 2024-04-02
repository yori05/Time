// Property of Florian Hulin, shouldn't be used without my consent.

#pragma once

#include "CoreMinimal.h"
#include "Component/TimeManipulator/Base_TimeManipulatorComponent.h"
#include "Components/ActorComponent.h"
#include "Enum/TimeManipulatorEnum.h"
#include "Enum/ManagerAuthority.h"

#include "Manager_TMComponent_Basic.generated.h"

/**-----------------	Exterior class declaration		-----------------*/
class UTimeManipulatorComponent_Basic;

/**
*  Manager Time Manipulator Component Basic :
* Part of the Time Manipulator System
* 
* Child of @Base_TimeManipulatorComponent 
* TimeState and Time evolution are handle by the parent class
* 
* This component should be add on a game mode because the components whome will search for him will try to access it from a game mode
* A component used to manage other Time manipulator components, these component are add on every component that should use Time manipulator system
* See @UTimeManipulatorComponent_Basic or child of this class for component using it.
* He save and direct Time manipulator component on other actor, tell them when come back in time, hold or go forward in time
* 
*/
UCLASS( ClassGroup=(TimeManipulator), meta=(BlueprintSpawnableComponent) )
class TIME_API UManager_TMComponent_Basic : public UBase_TimeManipulatorComponent
{
	GENERATED_BODY()

	/**-----------------	Variable Part		-----------------*/
	/**======	Component Management Part		======*/
protected:

	/**
	*  Array of Time Manipulator Component registered by this component
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time Management", meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UTimeManipulatorComponent_Basic>> TMComponents;

	/**
	* bSearchTimeManipulatorComponents :
	* Define if this manager should search component on begin play,
	* Usefull in case Time Manipulator Component can be load before this manager
	* Component should still try to find and link themself to this manager even if he search for them before.
	* Wont cause issues in case he try to link himself to already linked component
	*
	* Really heavy loop through every actor to check if they have a Time Manipulator Component should'nt be used if not needed
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Management", meta = (AllowPrivateAccess = "true"))
	bool bSearchTMComps = false;

	/**
	* ManagerAuthority :
	* Can this mananger update the time and launch record for the curve on every component or should he let the component update themself
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Management", meta = (AllowPrivateAccess = "true"))
	EManagerAuthority ManagerAuthority = EManagerAuthority::MANAGERAUTHORITY_Listen;

	/**======	Time Management Part		======*/
protected:

	/**
	* TMState_AtZero :
	* Define the TimeManipulatorState to change when the @TMState_Current is set as TMS_Backward and the @TimeSaved try to go under zero
	* Activated by @bChangeAtZero
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (AllowPrivateAccess = "true"))
	ETimeManipulatorState TMState_AtZero = ETimeManipulatorState::TMS_Forward;

	/**
	* bChangeAtZero :
	* Define if the manager should change the time state if time try to go under zero
	* Should work only if the time state is in backward mode
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (AllowPrivateAccess = "true"))
	bool bChangeAtZero = true;

	/**-----------------	Constructor Part		-----------------*/
public:	

	// Sets default values for this component's properties
	UManager_TMComponent_Basic();

	/**-----------------	Component Function Part		-----------------*/	
protected:

	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Called when the component is destroy
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	/**-----------------	Component Management Function Part		-----------------*/
public:

	/** Request for a component to be added on the array with every component */
	UFUNCTION(BlueprintCallable)
	virtual bool RequestAdd(UTimeManipulatorComponent_Basic* _NewComponent);

	/** Request for a component to be added on the array with every component */
	UFUNCTION(BlueprintCallable)
	virtual bool RequestRemove(UTimeManipulatorComponent_Basic* _NewComponent);

protected:

	/** 
	*  Search for every Time Manipulator Component on every actor on the scene 
	* Really heavy should'nt be used if not needed
	*/
	UFUNCTION(BlueprintCallable)
	virtual void SearchAllTMComps();

	/** Remove all Time Manipulator Component link to this manager */
	UFUNCTION(BlueprintCallable)
	virtual void RemoveAllTMComps();

	/**-----------------	Time Manipulator State Function Part		-----------------*/
public:

	/** Will launch the record state if it's doable */
	UFUNCTION(BlueprintCallable)
	virtual void LaunchRecordState();

	/** Verification if can the manager can launch record state */
	UFUNCTION(BlueprintCallable)
	virtual bool CanLaunchRecordState();

	/** Will launch the stop state if it's doable */
	UFUNCTION(BlueprintCallable)
	virtual void LaunchStopState();

	/** Verification if can the manager can launch stop state */
	UFUNCTION(BlueprintCallable)
	virtual bool CanLaunchStopState();

	/** Will launch the replay state if it's doable */
	UFUNCTION(BlueprintCallable)
	virtual void LaunchReplayState();

	/** Verification if can the manager can launch replay state */
	UFUNCTION(BlueprintCallable)
	virtual bool CanLaunchReplayState();

	/**======	Perform State Part		======*/
protected:

	/**
	*  Perform Replay state
	* Action take on the tick of the component on this step
	* Currently used when the time is set as Backward
	*/
	virtual void TickReplayState(float _DeltaTime) override;

	/**-----------------	Accessor Part		-----------------*/
public:

	FORCEINLINE TArray<TObjectPtr<UTimeManipulatorComponent_Basic>> GetTMComponents() { return TMComponents; }
};
