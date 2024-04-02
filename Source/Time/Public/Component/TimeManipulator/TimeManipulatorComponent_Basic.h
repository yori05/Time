// Property of Florian Hulin, shouldn't be used without my consent.

#pragma once

#include "CoreMinimal.h"
#include "Component/TimeManipulator/Base_TimeManipulatorComponent.h"
#include "Enum/TimeManipulatorEnum.h"

#include "TimeManipulatorComponent_Basic.generated.h"

/**-----------------	Exterior class declaration		-----------------*/
class UManager_TMComponent_Basic;


/**
*  TimeManipulatorComponent_Basic
* Part of the Time Manipulator system
* Child of Base_TimeManipulatorComponent
* 
* A default time manipulator component will be linked to the TM component manager,
* Used to call event and function on change in the time state
* Set the action for the time and when and how should we call the curve add on child class of this component
* In case you want to add curve on this component you should use a child of this class
* 
* This component handle :
* -> Link with the manager time manipulator component
* -> Synchronisation with the manager
* 
*/
UCLASS( ClassGroup=(TimeManipulator), meta=(BlueprintSpawnableComponent) )
class TIME_API UTimeManipulatorComponent_Basic : public UBase_TimeManipulatorComponent
{
	GENERATED_BODY()

	/**-----------------	Friend Class Part		-----------------*/

	// Give access to private part of this class the manager class
	friend UManager_TMComponent_Basic;

	/**-----------------	Variable Part		-----------------*/
	/**======	Component Management Part		======*/
protected:

	/** 
	*  Manager Ref :
	* Reference of the manager
	* Can be null
	* If you want an non null value use the function @AccessManagerRef() will set this value at the same time as returning it
	* Will be set if null when linked with the manager
	* 
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Time", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UManager_TMComponent_Basic> ManagerRef;

	/**
	* bSelfAuthority :
	* Can this component update the time and launch record for the curve himself or should he wait for the manager to launch update of time
	* Can be ignored if the manager force this component down
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Activity", meta = (AllowPrivateAccess = "true"))
	bool bSelfAuthority = true;

	/**
	* bForcedDown :
	* Will be set as true if the component is defined as self authority but the manager have full authority
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Activity", meta = (AllowPrivateAccess = "true"))
	bool bForcedDown = false;

	/**-----------------	Constructor Part		-----------------*/
public:	

	// Sets default values for this component's properties
	UTimeManipulatorComponent_Basic();

	/**-----------------	Component Function Part		-----------------*/
protected:

	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Called when the game end
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	/**-----------------	Management Function Part		-----------------*/
protected:

	/**
	* Return the manager reference
	* In case the reference is null will search for the manager and set reference value
	* Use automatically in the begin play
	*/
	UFUNCTION(BlueprintCallable)
	virtual UManager_TMComponent_Basic* AccessManagerRef();

	/**
	* Request link to the manager :
	* -> Add it in a array to be able to interact with it
	* -> Add function to callback
	*/
	UFUNCTION(BlueprintCallable)
	virtual void RequestLinkToManager();

	/**
	* Remove link to the manager :
	* -> remove it in from the array
	* -> remove function to callback
	*/
	UFUNCTION(BlueprintCallable)
	virtual void RemoveLinkToManager();

	/**
	* Force the component to listen to his manager in case the manager have full power and this component have self authority
	*/
	UFUNCTION(BlueprintCallable)
	virtual void ForceDown();

	/**
	* Liberate the component by the manager in case the manager had full authority and this component were forced to listen
	*/
	UFUNCTION(BlueprintCallable)
	virtual void LiberateAuthority();

	/**
	*  Link this component to the manager's callback
	*/
	UFUNCTION(BlueprintCallable)
	virtual void LinkToCallback();

	/**
	*  Break link between this component and the manager's callback
	*/
	UFUNCTION(BlueprintCallable)
	virtual void BreakLinkToCallback();

	/**
	*  Will synchronise time and TMState with the manager
	*/
	UFUNCTION(BlueprintCallable)
	virtual void SynchroniseWitchManager();

	/**-----------------	Time Evolution Function Part		-----------------*/
	/**======	Time Parameter Part		======*/
protected:

	/**
	*  Verification if @CallUpdateTime can function
	* This component need his self full autority to fuction
	*/
	virtual bool CanUpdateTime() override;

	/**
	* Update Times for this component
	* Update @TimeSaved at the same time as @TimeElapsed
	* Add / Out @_DeltaTime to @TimeElapsed until he is egal to @TimeStep of the manager or zero in case time is reversed (@bReverse)
	* In case @TimeElapsed satisfy one of this condition the manager should call @OnStepMade
	*
	*/
	UFUNCTION(BlueprintCallable)
	virtual void UpdateTimeByManager(float _DeltaTime);

	/**======	Step Action Part		======*/
protected :
	
	/**
	*  Verification if @CallStepMade can function
	* This component need his self full autority to fuction
	*/
	virtual bool CanStepMade() override;

	/**
	*  Called the a step is made by the manager, will reset the elapsed time to the same value as the manager
	* Will call every function link to @CallStepMade()
	*/
	UFUNCTION(BlueprintCallable)
	virtual void CallStepMadeByManager();

	/**-----------------	Accessor Part		-----------------*/
public:
 
	FORCEINLINE bool GetHasSelfAuthority() { return bSelfAuthority; };

	FORCEINLINE bool GetIsForcedDown() { return bForcedDown; };

	FORCEINLINE UManager_TMComponent_Basic* GetManagerRef() { return ManagerRef; };
};
