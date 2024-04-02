// Property of Florian Hulin, shouldn't be used without my consent.

#pragma once

#include "CoreMinimal.h"
#include "PlayerController/PlayerController_Basic.h"
#include "PlCont_TimeManipulator.generated.h"


/**-----------------	Exterior class declaration		-----------------*/
class UManager_TMComponent_Basic;

/**-----------------	Log definition Part		-----------------*/
DECLARE_LOG_CATEGORY_EXTERN(LogPlayerControllerTM, Log, All);


/**
 *  PlayerController_TimeManipulator
 * Connection for the TimeManipulator system and the Basic system
 * 
 * A player controller specialize to play input action in a TimeManipulator Game Mode
 * Will interact with Manager_TMComponent
 * 
 */
UCLASS(ClassGroup = (TimeManipulator))
class TIME_API APlCont_TimeManipulator : public APlayerController_Basic
{
	GENERATED_BODY()
	

	/**-----------------	Variable Part		-----------------*/
	/**======	Component Part		======*/

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Time", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UManager_TMComponent_Basic> TM_ManagerRef;

	/**======	Input Part		======*/

private:

	///** MappingContext */
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	//TObjectPtr<UInputMappingContext> TMMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> BackwardTimeAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ForwardTimeAction;

	/**-----------------	Inherit Function Part		-----------------*/
protected:

	// APawn interface
	virtual void SetupInputComponent() override;

	// To add mapping context
	virtual void BeginPlay() override;

	/**-----------------	Input Function Part		-----------------*/
protected:

	// Will call the manager of time manipulator and make the time goes backward
	UFUNCTION(BlueprintCallable)
	virtual void MakeBackwardTime();

	// Verification if the player can make the time goes backward
	UFUNCTION(BlueprintCallable)
	virtual bool CanBackwardTime();

	// Will call the manager of time manipulator and make the time goes forward
	UFUNCTION(BlueprintCallable)
	virtual void MakeForwardTime();

	// Verification if the player can make the time goes forward
	UFUNCTION(BlueprintCallable)
	virtual bool CanForwardTime();
};
