// Property of Florian Hulin, shouldn't be used without my consent.

#pragma once

/**-----------------	Include declaration		-----------------*/

#include "CoreMinimal.h"
#include "Component/TimeManipulator/TMComp_CurveBasic.h"

#include "TMComponent_PhysicsBasic.generated.h"

/**-----------------	Exterior class declaration		-----------------*/

class UCurveVector;
class UCurveFloat;
class UCurveLinearColor;
class UPrimitiveComponent;

/**
 *  Time Manpulator Component Physics Basic
 * Part of the Time Manipulator system
 * Child of UTimeManipulatorComponent_CurveBasic
 * 
 * This component use curve to record the basic stats of physics (location, rotation, scale)
 * Used to handle basic physic for actor of this component
 * You can handle or unhandle curve in case you don't use it
 * If you don't handle a part of it Curve won't be create,
 * you won't be able to handle a part of it in case you change it on runtime if you don't spawn the curve.
 * save the primitive component used manage the physic on this actor
 * 
 * This component handle :
 * -> Location
 * -> Rotation
 * -> Scale
 * 
 * On a later point an object whom regroup the curve, the object's the curve should handle, and a lambda function to update the curve / the object dependent of the state could be made
 */
UCLASS(ClassGroup = (TimeManipulator), meta = (BlueprintSpawnableComponent))
class TIME_API UTMComponent_PhysicsBasic : public UTMComp_CurveBasic
{
	GENERATED_BODY()
	
	/**-----------------	Variable Part		-----------------*/
protected:

	/**======	Primitive Component Management Part		======*/
	/**
	* Used to stop replay the phycis simulation on the actor owner when stop / backward time state
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPrimitiveComponent> SavedPhysicComponent;

	/**
	* Can this component stop physic simulation on Stop and Backward Time state
	* Set as true by default
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physics", meta = (AllowPrivateAccess = "true"))
	bool bStopPhysicOnState = true;

	/**======	Curves Part		======*/

	/** Curve use to record the location of the actor owner, use Time Step / Time Saved to set key */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCurveVector> LocationCurve;

	/** Curve use to record the rotation of the actor owner, use Time Step / Time Saved to set key */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCurveVector> RotationCurve;

//	/** Curve use to record the rotation of the actor owner, use Time Step / Time Saved to set key */
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation", meta = (AllowPrivateAccess = "true"))
//	TObjectPtr<UCurveLinearColor> RotationQuatCurve;

	/** Curve use to record the scale of the actor owner, use Time Step / Time Saved to set key */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scale", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCurveVector> ScaleCurve;

	/** Curve use to record the velocity of the actor owner, use Time Step / Time Saved to set key */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Velocity", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCurveVector> VelocityCurve;

	/** Curve use to record the angular velocity of the actor owner, use Time Step / Time Saved to set key */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Velocity", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCurveVector> AngularVelocityCurve;

	/**======	Data Part		======*/

	/** Used to save the location of the acter owner before record / replay it can be used on debug */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location", meta = (AllowPrivateAccess = "true"))
	FVector LocationVector;

	/** Used to calculate the lerp for the location of the acter owner before record / replay it can be used on debug */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Location", meta = (AllowPrivateAccess = "true"))
	FVector LocationVectorA;

	/** Used to calculate the lerp for the location of the acter owner before record / replay it can be used on debug */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Location", meta = (AllowPrivateAccess = "true"))
	FVector LocationVectorB;

	/** Used to save the rotation of the acter owner before record / replay it can be used on debug */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation", meta = (AllowPrivateAccess = "true"))
	FRotator RotationRotator;

	/** Used to calculate the lerp for the rotation of the acter owner before record / replay it can be used on debug */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rotation", meta = (AllowPrivateAccess = "true"))
	FRotator RotationRotatorA;

	/** Used to calculate the lerp for the rotation of the acter owner before record / replay it can be used on debug */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rotation", meta = (AllowPrivateAccess = "true"))
	FRotator RotationRotatorB;

	/**
	* Used to save the rotation of the acter owner before record / replay it can be used on debug
	* X = Pitch / Y = Yaw / Z = Roll
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation", meta = (AllowPrivateAccess = "true"))
	FVector RotationVector;

	/**
	* Used to calculate the lerp for the rotation of the acter owner before record / replay it can be used on debug
	* X = Pitch / Y = Yaw / Z = Roll
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rotation", meta = (AllowPrivateAccess = "true"))
	FVector RotationVectorA;

	/**
	* Used to calculate the lerp for the rotation of the acter owner before record / replay it can be used on debug
	* X = Pitch / Y = Yaw / Z = Roll
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rotation", meta = (AllowPrivateAccess = "true"))
	FVector RotationVectorB;

	/** Used to save the scale of the acter owner before record / replay it can be used on debug */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scale", meta = (AllowPrivateAccess = "true"))
	FVector ScaleVector;

	/** Used to save the velocity of the acter owner before record / replay it can be used on debug */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Velocity", meta = (AllowPrivateAccess = "true"))
	FVector VelocityVector;

	/** Used to save the angular velocity of the acter owner before record / replay it can be used on debug */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Velocity", meta = (AllowPrivateAccess = "true"))
	FVector AngularVelocityVector;

	/** Time scoped when we rewind it can be used on debug */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time", meta = (AllowPrivateAccess = "true"))
	float TimeScoped;

	/**======	Handle Part		======*/

	/** 
	* Can this component handle the location, will record it on Forwardand replay on Backward Time State 
	* Set as true by default
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location", meta = (AllowPrivateAccess = "true"))
	bool bHandleLocation = true;

	/** 
	* Can this component handle the rotation, will record it on Forwardand replay on Backward Time State 
	* Set as true by default
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation", meta = (AllowPrivateAccess = "true"))
	bool bHandleRotation = true;

	/**
	* Can this component handle the scale, will record it on Forwardand replay on Backward Time State
	* Set as false by default
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scale", meta = (AllowPrivateAccess = "true"))
	bool bHandleScale = false;

	/**
	* Can this component handle the velocity, will record it on Forwardand replay on Backward Time State
	* Set as true by default
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Velocity", meta = (AllowPrivateAccess = "true"))
	bool bHandleVelocity = true;

	/**
	* Can this component handle the angular velocity, will record it on Forwardand replay on Backward Time State
	* Set as true by default
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Velocity", meta = (AllowPrivateAccess = "true"))
	bool bHandleAngularVelocity = true;

	/**-----------------	Constructor Part		-----------------*/
public:

	// Sets default values for this component's properties
	UTMComponent_PhysicsBasic();

	/**-----------------	Inherit Function Part		-----------------*/
protected:

	// Called when the game starts
	virtual void BeginPlay() override;

	/**-----------------	Time State Part		-----------------*/
public:

	/**
	* Action on the activation record on this component
	* Currently used when the time is set as Forward
	*/
	virtual void ActivateRecordState() override;

	/**
	* Action on the activation stop on this component
	* Currently used when the time is set as Hold
	*/
	virtual void ActivateStopState() override;

	/**
	* Action on the activation replay on this component
	* Currently used when the time is set as Backward
	*/
	virtual void ActivateReplayState() override;

	/**-----------------	Curve Creation / Destroy Part		-----------------*/
protected:

	/**
	* Create all the curves on this component
	*/
	virtual void CreateCurves() override;

	/**
	* Create physics handler curves on this component
	* Won't Create a curve in case the handle of the curve is set as false
	* (Check @bHandleLocation, ...)
	* 
	* Called by @CreateCurves
	*/
	virtual void CreatePhysicsCurves();

	/**
	* Destroy all the curves on this component
	*/
	virtual void DestroyCurves() override;

	/**
	* Destroy physics handler curves on this component
	* 
	* Called by @DestroyCurves
	*/
	virtual void DestroyPhysicsCurves();


	/**-----------------	Set Curve Part		-----------------*/
protected:

	/** Reset all curves of this components  */
	virtual void ResetCurves() override;

	/** Reset the location curve of this actor  */
	UFUNCTION(BlueprintCallable)
	virtual void ResetLocationCurve();

	/** Reset the rotation curve of this actor  */
	UFUNCTION(BlueprintCallable)
	virtual void ResetRotationCurve();

	/** Reset the scale curve of this actor  */
	UFUNCTION(BlueprintCallable)
	virtual void ResetScaleCurve();

	/** Reset the velocity curve of this actor  */
	UFUNCTION(BlueprintCallable)
	virtual void ResetVelocityCurve();

	/** Reset the angular velocity curve of this actor  */
	UFUNCTION(BlueprintCallable)
	virtual void ResetAngularVelocityCurve();

	/**-----------------	Record Curve Part		-----------------*/
protected:

	/** Launch a call to record for all curves of this component  */
	virtual void RecordCurves() override;

	/** Launch a call to record the location curve  */
	UFUNCTION(BlueprintCallable)
	virtual void RecordLocationCurve();

	/** Launch a call to record the rotation curve  */
	UFUNCTION(BlueprintCallable)
	virtual void RecordRotationCurve();

	/** Launch a call to record the scale curve  */
	UFUNCTION(BlueprintCallable)
	virtual void RecordScaleCurve();

	/** Launch a call to record the velocity curve  */
	UFUNCTION(BlueprintCallable)
	virtual void RecordVelocityCurve();

	/** Launch a call to record the angular velocity curve  */
	UFUNCTION(BlueprintCallable)
	virtual void RecordAngularVelocityCurve();

	/**-----------------	Replay Curve Part		-----------------*/
protected:

	/** Launch a call to replay for curves of this component  */
	virtual void ReplayCurves() override;

	/** Launch a call to replay the location curve  */
	UFUNCTION(BlueprintCallable)
	virtual void ReplayLocationCurve();

	/** Launch a call to replay the rotation curve  */
	UFUNCTION(BlueprintCallable)
	virtual void ReplayRotationCurve();

	/** Launch a call to record the scale curve  */
	UFUNCTION(BlueprintCallable)
	virtual void ReplayScaleCurve();

	/** Launch a call to record the velocity curve  */
	UFUNCTION(BlueprintCallable)
	virtual void ReplayVelocityCurve();

	/** Launch a call to record the angular velocity curve  */
	UFUNCTION(BlueprintCallable)
	virtual void ReplayAngularVelocityCurve();

};
