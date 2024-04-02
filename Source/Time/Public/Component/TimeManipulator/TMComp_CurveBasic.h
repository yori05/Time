// Property of Florian Hulin, shouldn't be used without my consent.

#pragma once

#include "CoreMinimal.h"
#include "Component/TimeManipulator/TimeManipulatorComponent_Basic.h"
#include "TMComp_CurveBasic.generated.h"

/**
 *  UTimeManipulatorComponent_CurveBasic
 * Part of the TimeManipulatorSystem
 * Child of TimeManipulatorComponent_Basic
 * 
 * This component is used to link the curve with time of this component
 * His main job is to uniform action on this component curve with every child of this component and the time evolution
 * 
 * This component manage :
 * -> When we create curve
 * -> When we record curve
 * 
 * Will manage when curve should be created
 */
UCLASS(ClassGroup = (TimeManipulator), meta = (BlueprintSpawnableComponent))
class TIME_API UTMComp_CurveBasic : public UTimeManipulatorComponent_Basic
{
	GENERATED_BODY()
	
	/**-----------------	Constructor Part		-----------------*/
public:

	// Sets default values for this component's properties
	UTMComp_CurveBasic();

	/**-----------------	Inherit Function Part		-----------------*/
protected:

	// Called when the game starts
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Called when the game end
	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	/**-----------------	Curve Part		-----------------*/
protected:

	/**======	Creation / Destruction Part		======*/

	/**
	* Create curves on this component
	* Should use boolean as handle for the creation of curve
	*/
	UFUNCTION(BlueprintCallable)
	virtual void CreateCurves();

	/**
	* Destroy curves on this component
	* Should use boolean as handle for the creation of curve
	*/
	UFUNCTION(BlueprintCallable)
	virtual void DestroyCurves();


	/**======	Set / Reset Part		======*/

	/**
	* Set curves will make them start at the time of the component
	*/
	UFUNCTION(BlueprintCallable)
	virtual void SetCurves();

	/** Reset all curves of this components  */
	UFUNCTION(BlueprintCallable)
	virtual void ResetCurves();


	/**======	Record / Replay Part		======*/

	/**
	* Launch a call to record for all curves of this component
	* Called on @StepMade
	*/
	UFUNCTION(BlueprintCallable)
	virtual void RecordCurves();

	/**
	* Launch a call to replay for all curves of this component
	* Called on @TickReplayState
	*/
	UFUNCTION(BlueprintCallable)
	virtual void ReplayCurves();

	/**-----------------	Base Time Manipulator Function Part		-----------------*/
	/**======	Step Action Part		======*/
protected:

	// C++ Action take when a step is made
	virtual void StepMade() override;

	/**======	Perform State Part		======*/
protected:

	/**
	*	C++ Action take when procesing the tick of the replay state
	*/
	virtual void TickReplayState(float _DeltaTime) override;

};
